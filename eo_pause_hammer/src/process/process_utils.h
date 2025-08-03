#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

namespace process
{
    DWORD FindProcessIdByName(const std::wstring& processName);
} // namespace process6