#include <Windows.h>
#include <tlhelp32.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "PEHelper.h"
#include "Payload.h"

namespace fs = std::filesystem;

int main_unicode(int argc, wchar_t** argv) {
  int target_pid{0};
  std::wstring target_process{};
  std::wstring target_dll{};
  bool create_thread{true};

  for (int i = 1; i < argc; i++) {
    const auto& arg = argv[i];
    if (_wcsicmp(arg, L"--pid") == 0) {
      target_pid = _wtoi(argv[++i]);
    } else if (_wcsicmp(arg, L"--name") == 0) {
      target_process = argv[++i];
    } else if (_wcsicmp(arg, L"--dll") == 0) {
      target_dll = argv[++i];
    } else if (_wcsicmp(arg, L"--create-thread") == 0) {
      create_thread = true;
    } else if (_wcsicmp(arg, L"--no-create-thread") == 0) {
      create_thread = false;
    }
  }

  if (target_pid == 0) {
    if (target_process.empty()) {
      std::cerr << "ERR: `--pid` and `--name` missing.\n";
      return 1;
    }

    auto pids = PEHelper::Win32Process::FindProcessIdByName(target_process.c_str());
    if (pids.empty()) {
      std::cerr << "ERR: no process found by name.\n";
      return 2;
    } else if (pids.size() > 1) {
      std::cerr << "ERR: multiple process found, pid:\n";
      for (auto& pid : pids) {
        std::cerr << "  - " << pid << "\n";
      }
      std::cerr << "\n";
      return 3;
    }
    target_pid = pids[0];
  }
  if (target_dll.empty()) {
    std::cerr << "ERR: dll not specified.\n";
    return 4;
  }
  fs::path path_dll = fs::absolute(target_dll);
  if (!fs::exists(path_dll)) {
    std::cerr << "ERR: dll does not exist.\n";
    return 5;
  }
  target_dll = path_dll.wstring();

  std::vector<uint8_t> payload{0xE8, 0, 0, 0, 0};
  uint16_t strLen = static_cast<uint16_t>(target_dll.size() * 2);
  payload.push_back(static_cast<uint8_t>(strLen));
  payload.push_back(static_cast<uint8_t>(strLen >> 8));
  strLen += 2;
  payload.push_back(static_cast<uint8_t>(strLen));
  payload.push_back(static_cast<uint8_t>(strLen >> 8));
  for (auto& chr : target_dll) {
    payload.push_back(static_cast<uint8_t>(chr));
    payload.push_back(static_cast<uint8_t>(chr >> 8));
  }
  payload.push_back(0);
  payload.push_back(0);
  *(uint32_t*)&payload.at(1) = static_cast<uint32_t>(payload.size() - 5);

  PEHelper::Win32Process proc(target_pid);

  if (proc.IsProcessX86()) {
    auto span_payload = Payload::GetPayloadX86();
    payload.insert(payload.end(), span_payload.begin(), span_payload.end());
  } else if (proc.IsProcessX64()) {
    auto span_payload = Payload::GetPayloadX64();
    payload.insert(payload.end(), span_payload.begin(), span_payload.end());
  } else {
    fprintf_s(stderr, "ERR: payload does not support this arch: 0x%04x.\n", proc.GetProcessType());
    return 6;
  }

  auto remote_ptr = proc.SetupShellCode(payload.data(), payload.size());

  if (!create_thread) {
    fprintf_s(stderr, "Ready: %p\n", remote_ptr->Get());
    remote_ptr->KeepMemory();
  } else {
    auto ptr = remote_ptr->Get();
    remote_ptr->KeepMemory();
    fprintf_s(stderr, "Running: %p\n", ptr);

    uint32_t thread_error{};
    HANDLE hThread = proc.CreateThread(ptr, nullptr, thread_error);
    if (thread_error != 0) {
      fprintf_s(stderr, "WoW64_CreateRemoteThread failed: %08x\n", thread_error);
      return 8;
    }

    if (hThread == nullptr || hThread == INVALID_HANDLE_VALUE) {
      fprintf_s(stderr, "ERROR: could not create remote thread.\n");
      return 7;
    }

    auto wait_result = WaitForSingleObject(hThread, INFINITE);
    DWORD exitCode{0};
    if (GetExitCodeThread(hThread, &exitCode)) {
      fprintf_s(stderr, "module available at: 0x%08x\n", (exitCode));
    } else {
      fprintf_s(stderr, "get exit code for thread failed\n");
    }
  }

  return 0;
}

int main() {
  int argc{0};
  auto** argv = CommandLineToArgvW(GetCommandLineW(), &argc);

  return main_unicode(argc, argv);
}
