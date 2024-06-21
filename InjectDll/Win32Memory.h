#pragma once
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace PEHelper {

enum class Win32AllocType {
  NtAllocate = 0,
  VirtualAllocEx = 1,
};

class Win32MemoryAlloc {
 public:
  Win32MemoryAlloc(HANDLE hProcess, SIZE_T len, DWORD protect);
  inline ~Win32MemoryAlloc() { Free(); };
  inline void* operator*() const { return ptr_; }
  inline void* Get() { return ptr_; }
  void Free();
  bool ReAlloc(SIZE_T len);
  void KeepMemory();

 private:
  HANDLE hProcess_{nullptr};
  DWORD protect_{0};
  Win32AllocType type_{0};
  void* ptr_{nullptr};
  SIZE_T len_{0};
};

};  // namespace PEHelper
