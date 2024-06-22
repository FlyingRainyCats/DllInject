#include "pch.h"
#include <cstdio>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      MessageBoxW(nullptr, L"Hello World!", L"Hello?", MB_ICONINFORMATION);
      break;

    case DLL_THREAD_ATTACH:
      puts("DLL_THREAD_ATTACH");
      break;

    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
