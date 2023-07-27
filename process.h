#pragma once
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>

namespace process
{
	DWORD GetPID(const wchar_t* pName);
	uintptr_t GetBaseAddress(DWORD procId, const wchar_t* modName);
}

