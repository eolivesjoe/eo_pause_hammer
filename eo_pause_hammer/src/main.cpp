#include <iostream>
#include <thread>

#include "process/process_utils.h"
#include "process/thread_manager.h"
#include "hotkeys/hotkey_handler.h"
#include "logger/logger.h"

int wmain(int argc, wchar_t* argv[])
{
    logger::Init();
    if (argc < 2)
    {
        logger::Error("no arguments...");
        return 0;
    }

    auto pid = process::FindProcessIdByName(argv[1]);
    
    if (pid == 0)
    {
        logger::Error("process not found...");
        return 0;
    }

    process::ThreadManager manager(pid);
    hotkeys::Handler handler(manager);
    std::thread hotkeyThread(&hotkeys::Handler::Listener, &handler);

    hotkeyThread.join();

    return 0;
}
