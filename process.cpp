#include "process.h"

DWORD process::GetPID(const wchar_t* pName) {

	DWORD pid{};
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	//Iterates through every process until it finds one with a matching name
	if (hSnap != INVALID_HANDLE_VALUE) {

		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, pName)) {		
					pid = procEntry.th32ProcessID;
					break;

				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}

	CloseHandle(hSnap);

	return pid;
}

uintptr_t process::GetBaseAddress(DWORD procId, const wchar_t* modName) {

	uintptr_t modBaseAddr{};
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE) {

		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (Module32First(hSnap, &modEntry)) {

			do {

				if (!_wcsicmp(modEntry.szModule, modName)) {

					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;

				}

			} while (Module32Next(hSnap, &modEntry));
		}

	}

	CloseHandle(hSnap);

	return modBaseAddr;
}