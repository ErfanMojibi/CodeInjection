#include "DllIjnection.h"

int DllInjectSimple(char* DllPath, int ProcessId) {
	// open process
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);

	// allocate memory for dll path
	LPVOID DllPathAddress = VirtualAllocEx(hProcess, NULL, strlen(DllPath), MEM_COMMIT, PAGE_READWRITE);

	// write dll path to allocated memory
	WriteProcessMemory(hProcess, DllPathAddress, DllPath, strlen(DllPath), NULL);

	// get LoadLibraryA address
	LPVOID LoadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");

	// create remote thread
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryAddress, DllPathAddress, 0, NULL);

	// wait for thread to finish
	WaitForSingleObject(hThread, INFINITE);

	// close handle
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return 0;
}