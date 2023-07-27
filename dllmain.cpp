// dllmain.cpp : Defines the entry point for the DLL application.
#include "memedit.h"
#include "process.h"

DWORD WINAPI HackThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "DLL attached to process\n";

    //Get mBase address
    uintptr_t moduleBase = (intptr_t)GetModuleHandle(L"Stronghold_Crusader_Extreme.exe");

    //Hacks: Add resources, king godmode, freeze popularity, instant peasant respawn, no food needed, increase gamespeed
    bool bAddResource{ false }, bGodMode{ false }, bFreezePopularity{ false }, bInstantPeasant{ false };


    //Hack loop
    while (true) {
        //Get inputs
        if (GetAsyncKeyState(VK_END) & 1) {
            std::cout << "DLL ejected\n";
            break;
        }

        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bAddResource = !bAddResource;
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bGodMode = !bGodMode;
            if (bGodMode) {
                std::cout << "Godmode enabled\n";
            }
            else {
                std::cout << "Godmode disabled\n";
            }
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bFreezePopularity = !bFreezePopularity;
            if (bFreezePopularity) {
                std::cout << "Popularity frozen\n";
            }
            else {
                std::cout << "Popularity defrozen\n";
            }
        }

        if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
            bInstantPeasant = !bInstantPeasant;
            if (bInstantPeasant) {
                std::cout << "Peasants will now respawn instantly\n";
            }
            else {
                std::cout << "Peasants will now respawn normally\n";
            }
        }

        //Godmode
        uintptr_t* kingHpPtr = (uintptr_t*)(moduleBase + 0x109b27c);

        if (kingHpPtr) {
            if (bGodMode) {
                *(int*)(kingHpPtr) = 150000;
            }
        }

        //Popularity freeze
        uintptr_t* popularityPtr = (uintptr_t*)(moduleBase + 0xe3025c);

        if (popularityPtr) {
            if (bFreezePopularity) {
                *(int*)(popularityPtr) = 10000;
            }
        }

        //Instant peasants
        uintptr_t* peasantCDPtr = (uintptr_t*)(moduleBase + 0xe30268);

        if (peasantCDPtr) {
            if (bInstantPeasant) {
                *(int*)(peasantCDPtr) = 4000; //CD is actually an int incremented every tick until it reaches 4000
            }
        }

        Sleep(5);
    }

    //Eject + Cleanup
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

