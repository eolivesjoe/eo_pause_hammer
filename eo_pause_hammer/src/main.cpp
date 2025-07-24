#include <iostream>
#include <thread>

#include "process/process_utils.h"
#include "process/thread_manager.h"
#include "hotkeys/hotkey_handler.h"
#include "logger/logger.h"

int wmain(int argc, wchar_t* argv[])
{
    logger::init();
    if (argc < 2)
    {
        logger::error("no arguments...");
        return 0;
    }

    auto pid = process::findProcessIdByName(argv[1]);
    
    if (pid == 0)
    {
        logger::error("process not found...");
        return 0;
    }

    process::ThreadManager manager(pid);
    hotkeys::Handler handler(manager);
    std::thread hotkeyThread(&hotkeys::Handler::listener, &handler);

    hotkeyThread.join();

    return 0;
}
