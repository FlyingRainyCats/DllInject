#include "PEHelper.h"
#include <cstring>

#include <Windows.h>
#include <tlhelp32.h>

std::vector<uint32_t> PEHelper::Win32Process::FindProcessIdByName(
    const wchar_t* name) {
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

typedef decltype(&IsWow64Process2) tIsWowProcess2;

PEHelper::Win32Process::Win32Process(uint32_t pid) {
  hProcess_ = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE |
                              PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION,
                          FALSE, pid);
  auto IsWow64Process2fn = (tIsWowProcess2)GetProcAddress(
      GetModuleHandle(TEXT("kernel32.dll")), "IsWow64Process2");
  if (IsWow64Process2fn != nullptr) {
    IsWow64Process2fn(hProcess_, &machine_type_, nullptr);
  } else {
    // Fallback to older OS (Win7?)
    SYSTEM_INFO info{};
    GetNativeSystemInfo(&info);
    BOOL isWow64{false};
    if (IsWow64Process(hProcess_, &isWow64)) {
      const auto& arch = info.wProcessorArchitecture;

      // 32 bit, or 32-bit process running under WoW64.
      auto isProcessX86 = arch == PROCESSOR_ARCHITECTURE_INTEL ||
                          (arch == PROCESSOR_ARCHITECTURE_AMD64 && isWow64);
      machine_type_ =
          isProcessX86 ? IMAGE_FILE_MACHINE_I386 : IMAGE_FILE_MACHINE_AMD64;
    }
  }
}

void* PEHelper::Win32Process::SetupShellCode(const uint8_t* code, size_t len) {
  size_t unused{0};
  void* ptr = VirtualAllocEx(hProcess_, nullptr, len, MEM_COMMIT | MEM_RESERVE,
                             PAGE_EXECUTE_READ);
  if (ptr)
    WriteProcessMemory(hProcess_, ptr, code, len, &unused);
  return ptr;
}

HANDLE PEHelper::Win32Process::CreateThread(void* ptr, void* param) {
  return CreateRemoteThread(hProcess_, nullptr, 0x40,
                            LPTHREAD_START_ROUTINE(ptr), param, 0, nullptr);
}
