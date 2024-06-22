use32

; WoW64_CreateRemoteThread (Proxy)
start:
	push ebp
	mov ebp, esp
	push 0x33
	call hg_change_mode

WoW64_CreateRemoteThread_x64_entry:
	use64
	push rbp
	mov rbp, rsp
	and rsp, -0x10 ; align stack
	sub rsp, 0x48  ; alloc some *extra* shadow space
	mov ecx, dword[rbp+0x10]
	mov edx, dword[rbp+0x14]
	; mov r8d, dword[rbp+0x18]
	xor r8, r8
	call WoW64_CreateRemoteThread_impl
	leave
	call hg_exit_x64

	use32
	mov esp, ebp
	mov esp, esp
	mov edx, esp
	push 'hell'
	push 'ollo'
	pop ebp
	ret

WoW64_CreateRemoteThread_impl:
  file 'WoW64_CreateRemoteThread_impl.asmbin'

hg_change_mode:
	retfd

hg_exit_x64:
	use64
	mov dword[rsp + 4], 0x23
	retfd
