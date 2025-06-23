#pragma once

#include <string>

namespace logger 
{
    void init();

    void info(const std::string& msg);
    void info(const std::wstring& msg);
    void info(const DWORD msg);

    void error(const std::string& msg);
    void error(const std::wstring& msg);
    void error(const DWORD msg);
} // namespace logger
