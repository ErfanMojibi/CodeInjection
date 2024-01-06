#include "Utils.h"

int GetPIDByName(char* ProcessName) {
	// get process snapshot
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(PROCESSENTRY32);

	// iterate through processes
	do {
		// compare process name
		if (!strcmp(ProcEntry.szExeFile, ProcessName)) {
			// return process id
			return ProcEntry.th32ProcessID;
		}
	} while (Process32Next(hSnapshot, &ProcEntry));

	// close handle
	CloseHandle(hSnapshot);

	// return 0 if process not found
	return 0;
}