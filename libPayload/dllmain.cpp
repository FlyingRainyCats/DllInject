#include "pch.h"

#include <Windows.h>
#include <winnt.h>
#include <winternl.h>
#include <cstddef>
#include <cstdint>

// 从 NtdllLdrLoadDll 扣字节码

__forceinline PPEB GetPEB() {
#if defined(_M_X64)
  auto ptr = (PTEB)__readgsqword(offsetof(NT_TIB, Self));
#elif defined(_M_IX86)
  auto ptr = (PTEB)__readfsdword(offsetof(NT_TIB, Self));
#else
#error Unsupported arch for TEB.
#endif
  return ptr->ProcessEnvironmentBlock;
}

template <typename T>
__forceinline T my_inline_upper(T v) {
  if (v >= T{'a'} && v <= T{'z'}) {
    v += ('A' - 'a');
  }
  return v;
}

template <typename T, bool IGNORE_CASE = true>
__forceinline bool my_inline_str_eq(const T* a, const T* b) {
  if (a == b) {
    return true;
  }

  if (a == nullptr || b == nullptr) {
    return false;
  }

  for (T va{*a}, vb{*b};; va = *++a, vb = *++b) {
    if constexpr (IGNORE_CASE) {
      va = my_inline_upper(va);
      vb = my_inline_upper(vb);
    }

    if (va != vb) {
      return false;
    }

    if (va == 0) {
      return true;
    }
  }
}

__forceinline void* GetDllHandle(const wchar_t* name) {
  auto peb = GetPEB();
  LIST_ENTRY* list = &peb->Ldr->InMemoryOrderModuleList;

  for (auto link = list->Flink; link != list; link = link->Flink) {
    PLDR_DATA_TABLE_ENTRY entry =
        CONTAINING_RECORD(link, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

    // Search for NTDLL
    size_t len =
        entry->FullDllName.Length / sizeof(entry->FullDllName.Buffer[0]);
    const wchar_t* name_p = &entry->FullDllName.Buffer[len];
    while (name_p[-1] != L'\\')
      name_p--;

    if (my_inline_str_eq(name_p, name)) {
      return (void*)entry->DllBase;
    }
  }
  return nullptr;
}

__forceinline void* FindExport(void* base,
                               PIMAGE_EXPORT_DIRECTORY pEAT,
                               char* name) {
  if (pEAT == nullptr) {
    return nullptr;
  }

  auto va = [&base](int offset) -> void* { return (uint8_t*)(base) + offset; };
  auto p_export_fns = (uint32_t*)va(pEAT->AddressOfFunctions);
  auto p_export_ords = (uint16_t*)va(pEAT->AddressOfNameOrdinals);
  auto p_export_names = (uint32_t*)va(pEAT->AddressOfNames);

  auto n_number_of_names = (uint32_t)pEAT->NumberOfNames;
  for (uint32_t i = 0; i < n_number_of_names; i++) {
    auto p_fn_name = (char*)va(p_export_names[i]);

    if (my_inline_str_eq<char, false>(name, p_fn_name)) {
      return va(p_export_fns[p_export_ords[i]]);
    }
  }
  return nullptr;
}

typedef NTSTATUS(NTAPI* tLdrLoadDll)(_In_opt_ PWSTR DllPath,
                                     _In_opt_ PULONG DllCharacteristics,
                                     _In_ PUNICODE_STRING DllName,
                                     _Out_ PVOID* DllHandle);

extern "C" __declspec(dllexport) void* __fastcall NtdllLdrLoadDll(
    PUNICODE_STRING dllName) {
  wchar_t szNtdll[] = {L'N', L'T', L'D', L'L', L'L', L'.', L'D', L'L', L'L', 0};
  char szLdrLoadDll[] = {'L', 'd', 'r', 'L', 'o', 'a', 'd', 'D', 'l', 'l', 0};
  auto* peNtdll = (uint8_t*)GetDllHandle(szNtdll);
  if (peNtdll) {
    auto& pOptHeader =
        PIMAGE_NT_HEADERS(peNtdll + PIMAGE_DOS_HEADER(peNtdll)->e_lfanew)
            ->OptionalHeader;
    auto& pEATTable = pOptHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    auto pEAT = PIMAGE_EXPORT_DIRECTORY(peNtdll + pEATTable.VirtualAddress);
    auto LdrLoadDllFn = (tLdrLoadDll)FindExport(peNtdll, pEAT, szLdrLoadDll);
    if (LdrLoadDllFn) {
      void* handle{nullptr};
      LdrLoadDllFn(nullptr, nullptr, dllName, &handle);
      return handle;
    }
  }

  return nullptr;
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
