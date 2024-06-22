// TestPayload.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Windows.h>
#include <iostream>

extern "C" __declspec(dllimport) HANDLE CRT_WoW64_ToNative(DWORD hProcess, DWORD addr, DWORD* hThread);

void fn() {
  MessageBoxA(0, "A", "B", MB_ICONINFORMATION);
}

int main() {
  auto hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());

  MEM_ADDRESS_REQUIREMENTS mem_param_max_addr{};
  mem_param_max_addr.HighestEndingAddress = (void*)(uintptr_t)0x7EFF'FFFF;

  MEM_EXTENDED_PARAMETER param{};
  param.Type = MemExtendedParameterAddressRequirements;
  param.Pointer = &mem_param_max_addr;

  auto shellcode = VirtualAlloc2(hProc, nullptr, 4096, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE, &param, 1);

  if (shellcode == nullptr) {
    fprintf_s(stderr, "ERR: could not alloc memory, error code: %d\n", GetLastError());
    return 1;
  }

  auto ptr_fn = (uintptr_t)(&fn);
  *(uint8_t*)shellcode = 0x68;
  *(uint32_t*)((uint8_t*)shellcode + 1) = ptr_fn & 0xFFFF'FFFF;
  *(uint32_t*)((uint8_t*)shellcode + 5) = 0x042444C7;
  *(uint32_t*)((uint8_t*)shellcode + 9) = static_cast<uint64_t>(ptr_fn) >> 32;
  *((uint8_t*)shellcode + 13) = 0xC3;

  CRT_WoW64_ToNative((DWORD)hProc, (DWORD)shellcode, nullptr);
  Sleep(INFINITE);
}
