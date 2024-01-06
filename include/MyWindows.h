#pragma once
#include <Windows.h>
typedef struct tagPROCESSENTRY32 {
	DWORD     dwSize;
	DWORD     cntUsage;
	DWORD     th32ProcessID;
	ULONG_PTR th32DefaultHeapID;
	DWORD     th32ModuleID;
	DWORD     cntThreads;
	DWORD     th32ParentProcessID;
	LONG      pcPriClassBase;
	DWORD     dwFlags;
	CHAR      szExeFile[MAX_PATH];
} PROCESSENTRY32;

#define TH32CS_SNAPPROCESS 0x00000002