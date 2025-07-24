#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

namespace process
{
    DWORD findProcessIdByName(const std::wstring& processName);
} // namespace process6