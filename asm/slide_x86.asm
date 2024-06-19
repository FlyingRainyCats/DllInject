use32

; ShellCode to load dll
; push unicode_str
; call _start

_start:
  pop ecx

  push ebp
  mov ebp, esp
  sub esp, 0x08

  mov eax, dword[ecx]
  mov dword[ebp-0x08], eax

  add ecx, 4
  mov dword[ebp-0x04], ecx
  lea ecx, [ebp-0x08]

  call _loadDll
  leave
  ret 4

_loadDll:
