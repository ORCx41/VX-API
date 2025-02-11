#include "Win32Helper.h"

HMODULE GetModuleHandleEx2A(_In_ LPCSTR lpModuleName)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	CHAR wDllName[64] = { 0 };
	PLIST_ENTRY Head = &Peb->LoaderData->InMemoryOrderModuleList;
	PLIST_ENTRY Next = Head->Flink;
	Module = (PLDR_MODULE)((PBYTE)Next - 16);

	while (Next != Head)
	{
		Module = (PLDR_MODULE)((PBYTE)Next - 16);
		if (Module->BaseDllName.Buffer != NULL)
		{
			ZeroMemoryEx(wDllName, sizeof(wDllName));
			WCharStringToCharString(wDllName, Module->BaseDllName.Buffer, 64);
			if (StringCompareA(lpModuleName, wDllName) == 0)
				return (HMODULE)Module->BaseAddress;
		}
	}

	return NULL;
}

HMODULE GetModuleHandleEx2W(_In_ LPCWSTR lpModuleName)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;

	PLIST_ENTRY Head = &Peb->LoaderData->InMemoryOrderModuleList;
	PLIST_ENTRY Next = Head->Flink;
	Module = (PLDR_MODULE)((PBYTE)Next - 16);

	while (Next != Head)
	{
		Module = (PLDR_MODULE)((PBYTE)Next - 16);
		if (Module->BaseDllName.Buffer != NULL)
		{
			if (StringCompareW(lpModuleName, Module->BaseDllName.Buffer) == 0)
				return (HMODULE)Module->BaseAddress;
		}

		Next = Next->Flink;
	}

	return NULL;
}