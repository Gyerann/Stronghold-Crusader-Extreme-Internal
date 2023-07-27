#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include  <TlHelp32.h>

namespace memedit
{
	void MemPatch(BYTE* destination, BYTE* source, unsigned int size);
	void NOP(BYTE* destination, unsigned int size);
}

