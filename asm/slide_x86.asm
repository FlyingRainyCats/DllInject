use32

_start:
  pop ecx
  call _loadDll
  ret 4

_loadDll:
