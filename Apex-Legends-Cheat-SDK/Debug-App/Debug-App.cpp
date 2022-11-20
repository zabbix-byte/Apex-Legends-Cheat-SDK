#include <iostream>
#include <filesystem>
#include "Driver.h"
#include "utils.h"

using namespace std;

uintptr_t GetPid(const wchar_t* processName)
{
	PROCESSENTRY32 procEntry32;
	uintptr_t pID = 0;

	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hProcSnap || hProcSnap == INVALID_HANDLE_VALUE)
		return 0;

	while (Process32Next(hProcSnap, &procEntry32))
	{
		if (!wcscmp(processName, procEntry32.szExeFile))
		{
			pID = procEntry32.th32ProcessID;

			CloseHandle(hProcSnap);
		}
	}

	CloseHandle(hProcSnap);
	return pID;
}

void OpenApex()
{
	ShellExecute(NULL, L"open", L"C:\\Program Files (x86)\\Origin Games\\Apex\\r5apex.exe", NULL, NULL, SW_SHOWDEFAULT);
}


int main()
{
    int i;
    cout << "<ZT-CHEATS> TESTING DRIVER\n";
   


    // int 

    if (GetPid(L"r5apex.exe") == 0) {

		//Map Driver
		system("kdmapper.exe DriverForApex.sys");
		system("cls");
		std::cout << "[-] ApexDriver mapped!" << std::endl;

		//WriteCustomSplashScreen(); //Replace EAC Splash Screen

		Sleep(1000);


		OpenApex();

		std::cout << GetPid(L"r5apex.exe") << std::endl; //When EAC is initally loaded
		Sleep(45000); //Allow time for apex to launch

		std::cout << "[?] Searching for process..." << std::endl;
	}


	while (!Globals::hWnd)
		Globals::hWnd = FindWindow(NULL, L"Apex Legends");

    while (!Globals::processID)
		Globals::processID = Driver::get_process_id("r5apex.exe");

    while (!Globals::modBase)
		Globals::modBase = Driver::GetModuleBase(Globals::processID, "r5apex.exe");
		std::cout << "[-] r5apex.exe found at " << std::hex << Globals::modBase << std::endl;

	if (Globals::processID) {
		//WriteDefaultSplashScreen(); //Reset EAC Splash Screen
	}

    cin >> i;
    return 0;
}
