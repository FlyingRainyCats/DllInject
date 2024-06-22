@echo off

fasm slide_x64.asm
fasm slide_x86.asm
fasm WoW64_CreateRemoteThread.asm

..\x64\Release\ShellCodeToMasm.exe ^
  WoW64_CreateRemoteThread.bin ^
  ..\InjectDll\WoW64_CreateRemoteThread.asm ^
  WoW64_CreateRemoteThread
echo rc: %ERRORLEVEL%

pause
