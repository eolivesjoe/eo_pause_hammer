#pragma once

#include <string>
#include <Windows.h>
#include <TlHelp32.h>

namespace process
{
    // Finds the PID of the first process with the given name.
    DWORD findProcessIdByName(const std::wstring& processName);
} // namespace process