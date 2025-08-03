#include <iostream>
#include <Windows.h>

#include "logger.h"

namespace logger 
{
    void Init() 
    {
        std::ios::sync_with_stdio(false);
    }

    void Info(const std::string& msg)
    {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void Info(const std::wstring& msg)
    {
        std::wcout << "[INFO] " << msg << std::endl;
    }

    void Info(DWORD msg)
    {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void Error(const std::string& msg) 
    {
        std::cerr << "[ERROR] " << msg << std::endl;
    }

    void Error(const std::wstring& msg)
    {
        std::wcerr << "[ERROR] " << msg << std::endl;
    }

    void Error(DWORD msg)
    {
        std::cerr << "[ERROR] " << msg << std::endl;
    }
}