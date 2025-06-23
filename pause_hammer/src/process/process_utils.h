#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

namespace process
{
    // Finds the PID of the first process with the given name
    DWORD findProcessIdByName(const std::wstring& processName);
} // namespace process6