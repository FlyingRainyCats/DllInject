#include "Win32Memory.h"
#include <atomic>

// ntdll
typedef NTSTATUS(NTAPI* tNtAllocateVirtualMemory)(_In_ HANDLE ProcessHandle,
                                                  PVOID* BaseAddress,
                                                  _In_ ULONG_PTR ZeroBits,
                                                  _Inout_ PSIZE_T RegionSize,
                                                  _In_ ULONG AllocationType,
                                                  _In_ ULONG Protect);
typedef NTSTATUS(NTAPI* tNtFreeVirtualMemory)(_In_ HANDLE ProcessHandle,
                                              _Inout_ PVOID* BaseAddress,
                                              _Inout_ PSIZE_T RegionSize,
                                              _In_ ULONG FreeType);

tNtAllocateVirtualMemory fnNtAllocateVirtualMemory{};
tNtFreeVirtualMemory fnNtFreeVirtualMemory{};
bool gNtAllocAvailable{false};

PEHelper::Win32MemoryAlloc::Win32MemoryAlloc(HANDLE hProcess, SIZE_T len, DWORD protect) {
  static std::atomic<int> guard(0);
  if (guard.fetch_or(1) == 0) {
    if (auto hNtDll = LoadLibraryA("ntdll.dll")) {
      fnNtAllocateVirtualMemory = (tNtAllocateVirtualMemory)GetProcAddress(hNtDll, "NtAllocateVirtualMemory");
      fnNtFreeVirtualMemory = (tNtFreeVirtualMemory)GetProcAddress(hNtDll, "NtAllocateVirtualMemory");
      gNtAllocAvailable = fnNtAllocateVirtualMemory != nullptr && fnNtFreeVirtualMemory != nullptr;
    }
  }

  hProcess_ = hProcess;
  len_ = len;
  protect_ = protect;

  ReAlloc(len);
}

bool PEHelper::Win32MemoryAlloc::ReAlloc(SIZE_T len) {
  Free();

  len_ = len;

  // Prefer VirtualAlloc if we are Win64
#ifdef _WIN64
  ptr_ = VirtualAllocEx(hProcess_, nullptr, len, MEM_COMMIT | MEM_RESERVE, protect_);
  if (ptr_ != nullptr) {
    type_ = Win32AllocType::VirtualAllocEx;
    return true;
  }
#endif

  if (gNtAllocAvailable) {
    // Restrict address space when we are 32-bit.
    constexpr uint64_t kZeroBits = sizeof(void*) == 4 ? 0x7FFF'FFFF : 0;

    SIZE_T region_size{len};
    if (SUCCEEDED(fnNtAllocateVirtualMemory(hProcess_, &ptr_, (ULONG_PTR)kZeroBits, &region_size,
                                            MEM_COMMIT | MEM_RESERVE, protect_))) {
      type_ = Win32AllocType::NtAllocate;
      len_ = region_size;  // updated size
      return true;
    }
  }

  return false;
}

void PEHelper::Win32MemoryAlloc::KeepMemory() {
  ptr_ = nullptr;
}

void PEHelper::Win32MemoryAlloc::Free() {
  if (ptr_ == nullptr) {
    return;
  }

  switch (type_) {
    case Win32AllocType::NtAllocate:
      fnNtFreeVirtualMemory(hProcess_, &ptr_, &len_, MEM_RELEASE);
      break;
    case Win32AllocType::VirtualAllocEx:
      VirtualFreeEx(hProcess_, ptr_, 0, MEM_RELEASE);
      break;
  }

  ptr_ = nullptr;
}