#include "monitor.h"

bool doMonitor(int& err, std::wstring &exename)
{
	err = 0; //reset error
	HWND activeWindow = GetForegroundWindow(); //NOT getactive window, as that is calling-thread specific

	DWORD procID;
	//get process ID of current window
	GetWindowThreadProcessId(activeWindow, &procID);

	//now we iterate through all processes to find associated .exe name with that process ID.
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, procID);

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		err = 1;
		return false;
	}

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(snapshot, &procEntry))
	{
		do
		{
			if (procEntry.th32ProcessID == procID)
			{
				//close
				CloseHandle(snapshot);

				exename = procEntry.szExeFile;
				return true;
			}
		} while (Process32Next(snapshot, &procEntry));
	}
	CloseHandle(snapshot);

	return false;
}