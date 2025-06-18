#include <iostream>
#include "utils/process_utils.h"
#include "process/thread_manager.h"
#include "hotkeys/hotkey_handler.h"
#include "logger/logger.h"

int main() 
{
    std::cout << "Hello\n";
    logger::init();
    logger::info("HELLO 1");
    logger::error("NOT HELLO");
    return 0;
}
