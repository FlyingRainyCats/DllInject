#include "PEHelper.h"
#include <cstring>

#include <Windows.h>
#include <tlhelp32.h>

std::atomic<int> PEHelper::Win32Process::init_guard_{0};
PEHelper::tIsWowProcess2 PEHelper::Win32Process::fnIsWowProcess2{nullptr};
PEHelper::tVirtualAlloc2 PEHelper::Win32Process::fnVirtualAlloc2{nullptr};

std::vector<uint32_t> PEHelper::Win32Process::FindProcessIdByName(const wchar_t* name) {
  std::vector<uint32_t> pids{};
  PROCESSENTRY32 pe{};
  pe.dwSize = sizeof(pe);

  auto hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (Process32First(hSnap, &pe)) {
    do {
      if (_wcsicmp(name, pe.szExeFile) == 0) {
        pids.push_back(pe.th32ProcessID);
      }
    } while (Process32Next(hSnap, &pe));
  }
  CloseHandle(hSnap);
  return pids;
}

USHORT PEHelper::Win32Process::GetProcessArchFromProcess() const {
  if (fnIsWowProcess2) {
    USHORT process_machine{IMAGE_FILE_MACHINE_UNKNOWN};
    USHORT native_machine{IMAGE_FILE_MACHINE_UNKNOWN};

    // When not running under WoW64, process_machine is "IMAGE_FILE_MACHINE_UNKNOWN".
    // We should use the value from native_machine instead.
    if (fnIsWowProcess2(hProcess_, &process_machine, &native_machine)) {
      return process_machine == IMAGE_FILE_MACHINE_UNKNOWN ? native_machine : process_machine;
    }
  }

  // Fallback to older OS (Win7?)
  SYSTEM_INFO info{};
  GetNativeSystemInfo(&info);
  BOOL isWow64{false};
  if (IsWow64Process(hProcess_, &isWow64)) {
    const auto& arch = info.wProcessorArchitecture;

    // 32 bit, or 32-bit process running under WoW64.
    auto isProcessX86 = arch == PROCESSOR_ARCHITECTURE_INTEL || (arch == PROCESSOR_ARCHITECTURE_AMD64 && isWow64);
    return isProcessX86 ? IMAGE_FILE_MACHINE_I386 : IMAGE_FILE_MACHINE_AMD64;
  }

  return IMAGE_FILE_MACHINE_UNKNOWN;
}

PEHelper::Win32Process::Win32Process(uint32_t pid) {
  if (init_guard_.fetch_add(1) == 0) {
    if (auto hKernel32 = LoadLibraryA("kernel32.dll")) {
      fnIsWowProcess2 = (tIsWowProcess2)GetProcAddress(hKernel32, "IsWow64Process2");
      fnVirtualAlloc2 = (tVirtualAlloc2)GetProcAddress(hKernel32, "VirtualAlloc2");
    }

    // Try again from kernelbase :)
    if (fnVirtualAlloc2 == nullptr) {
      if (auto hKernelBase = LoadLibraryA("kernelbase.dll")) {
        fnVirtualAlloc2 = (tVirtualAlloc2)GetProcAddress(hKernelBase, "VirtualAlloc2");
      }
    }
  }

  constexpr DWORD kAccess =
      PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD;
  hProcess_ = OpenProcess(kAccess, FALSE, pid);
  machine_type_ = GetProcessArchFromProcess();
}

std::unique_ptr<PEHelper::Win32MemoryAlloc> PEHelper::Win32Process::SetupShellCode(const uint8_t* code, size_t len) {
  auto remote_ptr = std::make_unique<PEHelper::Win32MemoryAlloc>(hProcess_, len, PAGE_EXECUTE_READ);

  if (auto ptr = remote_ptr->Get()) {
    SIZE_T bytes_written{};
    WriteProcessMemory(hProcess_, ptr, code, len, &bytes_written);

    if (bytes_written == len) {
      return remote_ptr;
    }
  }

  return {};
}

#ifndef _WIN64
EXTERN_C uint32_t WoW64_CreateRemoteThread(HANDLE hProcess, void* ptr, HANDLE* hThread);
#endif

HANDLE PEHelper::Win32Process::CreateThread(void* ptr, void* param, uint32_t& error_code) {
  HANDLE hThread{};
  error_code = 0;

#if !defined(_WIN64) && defined(USE_WOW64_INJECT)
  // Are we trying to inject from WoW64 to Native X64
  if (IsProcessX64()) {
    uint32_t status = WoW64_CreateRemoteThread(hProcess_, ptr, &hThread);
    error_code = status;
    if (SUCCEEDED(status)) {
      return hThread;
    }
    return nullptr;
  }
#endif

  hThread = CreateRemoteThread(hProcess_, nullptr, 0x40, LPTHREAD_START_ROUTINE(ptr), param, 0, nullptr);
  if (hThread == nullptr) {
    error_code = GetLastError();
  }
  return hThread;
}
