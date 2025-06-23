#include "process_utils.h"

namespace process
{
	DWORD findProcessIdByName(const std::wstring& processName)
	{

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot == INVALID_HANDLE_VALUE)
		{
			return 0;
		}

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &entry) == TRUE)
		{
			do 
			{
				if (_wcsicmp(entry.szExeFile, processName.c_str()) == 0)
				{
					CloseHandle(snapshot);
					return entry.th32ProcessID;
				}
			} while (Process32Next(snapshot, &entry) == TRUE);
		}

		CloseHandle(snapshot);
		return 0;
	}
}