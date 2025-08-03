#pragma once

#include <string>

namespace logger 
{
    void Init();

    void Info(const std::string& msg);
    void Info(const std::wstring& msg);
    void Info(const DWORD msg);

    void Error(const std::string& msg);
    void Error(const std::wstring& msg);
    void Error(const DWORD msg);
} // namespace logger
