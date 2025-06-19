#include "process_utils.h"

namespace process
{
	DWORD findProcessIdByName(const std::wstring& processName)
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot == INVALID_HANDLE_VALUE)
		{
			return 0;
		}

		if (Process32First(snapshot, &entry) == true)
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