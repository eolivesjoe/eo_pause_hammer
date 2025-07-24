#include <iostream>
#include <Windows.h>

#include "logger.h"

namespace logger 
{
    void init() 
    {
        std::ios::sync_with_stdio(false);
    }

    void info(const std::string& msg)
    {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void info(const std::wstring& msg)
    {
        std::wcout << "[INFO] " << msg << std::endl;
    }

    void info(DWORD msg)
    {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void error(const std::string& msg) 
    {
        std::cerr << "[ERROR] " << msg << std::endl;
    }

    void error(const std::wstring& msg)
    {
        std::wcerr << "[ERROR] " << msg << std::endl;
    }

    void error(DWORD msg)
    {
        std::cerr << "[ERROR] " << msg << std::endl;
    }
}