# InjectDll

DLL ע����볢�ԡ�

## ʹ��

```pwsh
.\InjectDll.exe <--pid pid | --name "process.exe"> <--dll "C:/path/to/library.dll"> [--no-create-thread | --create-thread]

--pid                ָ������ ID
--name               ָ����������
--dll                ָ����Ҫע��� DLL
--create-thread      ע����������Զ���̵߳��� [Ĭ����Ϊ]
--no-create-thread   ע������ִ��
```

## ����

����Դ��ֱ�ӱ��뼴�ɡ�

### `dllLoaderX86`

�����ִ���ƴ�Ӷ��ɡ�

1. `asm/slide_x86.asm` ���뵽�ֽ���
2. `libPayload` ����󣬽� `NtdllLdrLoadDll` ���ֽ���ٳ���

## ��Ŀ˵��

- `DemoExe` - ����Ŀ�ꡣ
- `HelloDll` - ����ע��Ĳ��� DLL��
- `InjectDll` - ע����
- `libPayload` - �����������ֽ���

## ����˵��

Զ���߳�ע��Ƚ����ԣ�ɱ��������⡣

�� Windows Defender ��ֱ����Ϊʶ��`Behavior:Win32/DefenseEvasion.A!ml`��

## ֧�ֵ�ע�뷽��

- x64 ע���� -> ע�� x64 ����
- x64 ע���� -> ע�� x86 (WoW64) ����
- x86 ע���� -> ע�� x86 (WoW64) ����
- (ʵ���ԣ����� `USE_WOW64_INJECT` ����) x86 ע���� -> ע�� x64 ���̣�ע��ɹ����Ǳ���������ԭ��δ֪��
  - ��������֮��ʵ�֡�

## License

MIT License + ���պ��������ǳ�����������Ϊʦ˵�������ɡ�
