#include "DllIjnection.h"
#include "ShellcodeInjection.h"
#include "Utils.h"

int main()
{
	char* DllPath = "";
	DWORD pid = GetPIDByName("notepad.exe");
	printf("%d", pid);
	DllInjectSimple(DllPath, pid);

	return 0;
}