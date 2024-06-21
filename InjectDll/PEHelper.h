#pragma once
#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <memory>
#include <vector>
#include "Win32Memory.h"

namespace PEHelper {
typedef decltype(&IsWow64Process2) tIsWowProcess2;
typedef decltype(&VirtualAlloc2) tVirtualAlloc2;

class Win32Process {
 public:
  static std::vector<uint32_t> FindProcessIdByName(const wchar_t* name);

  Win32Process(uint32_t pid);
  inline bool IsProcessX64() const { return machine_type_ == IMAGE_FILE_MACHINE_AMD64; }
  inline bool IsProcessX86() const { return machine_type_ == IMAGE_FILE_MACHINE_I386; }
  inline bool IsProcessAarch64() const { return machine_type_ == IMAGE_FILE_MACHINE_ARM64; }
  inline uint16_t GetProcessType() const { return machine_type_; }
  std::unique_ptr<Win32MemoryAlloc> SetupShellCode(const uint8_t* code, size_t len);
  HANDLE CreateThread(void* ptr, void* param);

 private:
  HANDLE hProcess_;
  USHORT machine_type_{IMAGE_FILE_MACHINE_UNKNOWN};

  static std::atomic<int> init_guard_;
  static tIsWowProcess2 fnIsWowProcess2;
  static tVirtualAlloc2 fnVirtualAlloc2;
  USHORT GetProcessArchFromProcess() const;
};
}  // namespace PEHelper
