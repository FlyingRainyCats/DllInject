# InjectDll

DLL 注入代码尝试。

## 使用

```pwsh
.\InjectDll.exe <--pid pid | --name "process.exe"> <--dll "C:/path/to/library.dll"> [--no-create-thread | --create-thread]

--pid                指定进程 ID
--name               指定进程名称
--dll                指定需要注入的 DLL
--create-thread      注入代码后立即远程线程调用 [默认行为]
--no-create-thread   注入代码后不执行
```

## 编译

现有源码直接编译即可。

### `dllLoaderX86`

两部分代码拼接而成。

1. `asm/slide_x86.asm` 编译到字节码
2. `libPayload` 编译后，将 `NtdllLdrLoadDll` 的字节码抠出来

## 项目说明

- `DemoExe` - 测试目标。
- `HelloDll` - 用来注入的测试 DLL。
- `InjectDll` - 注入器
- `libPayload` - 用来编译后扣字节码

## 其他说明

远端线程注入比较明显，杀毒软件会检测。

如 Windows Defender 能直接行为识别：`Behavior:Win32/DefenseEvasion.A!ml`。

## 支持的注入方法

- x64 注入器 -> 注入 x64 进程
- x64 注入器 -> 注入 x86 (WoW64) 进程
- x86 注入器 -> 注入 x86 (WoW64) 进程
- (实验性，带上 `USE_WOW64_INJECT` 编译) x86 注入器 -> 注入 x64 进程，注入成功但是本体会崩溃，原因未知。
  - 利用天堂之门实现。

## License

MIT License + 【日后你若是惹出祸来，不把为师说出来即可】
