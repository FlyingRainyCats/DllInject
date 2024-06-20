#pragma once
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace PEHelper {
class Win32Process {
 public:
  static std::vector<uint32_t> FindProcessIdByName(const wchar_t* name);

  Win32Process(uint32_t pid);
  inline bool IsProcessX64() const {
    return machine_type_ == IMAGE_FILE_MACHINE_AMD64;
  }
  inline bool IsProcessX86() const {
    return machine_type_ == IMAGE_FILE_MACHINE_I386;
  }
  inline bool IsProcessAarch64() const {
    return machine_type_ == IMAGE_FILE_MACHINE_ARM64;
  }
  inline uint16_t GetProcessType() const { return machine_type_; }
  void* SetupShellCode(const uint8_t* code, size_t len);
  HANDLE CreateThread(void* ptr, void* param);

 private:
  HANDLE hProcess_;
  USHORT machine_type_{IMAGE_FILE_MACHINE_UNKNOWN};
};
}  // namespace PEHelper
