#include <iostream>

#include "process/process_utils.h"
#include "process/thread_manager.h"
#include "hotkeys/hotkey_handler.h"
#include "logger/logger.h"

int main() 
{
    logger::init();

    auto pid = process::findProcessIdByName(L"Firefox.exe");

    logger::info("pid");
    logger::info(pid);

    logger::info("threads");


    process::ThreadManager tm(pid);
    tm.togglePause();
    tm.togglePause();

    return 0;
}
