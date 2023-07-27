#include "memedit.h"

void memedit::MemPatch(BYTE* destination, BYTE* source, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(destination, source, size);
	VirtualProtect(destination, size, oldprotect, &oldprotect);
}

void memedit::NOP(BYTE* destination, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(destination, 0x90, size);
	VirtualProtect(destination, size, oldprotect, &oldprotect);
}