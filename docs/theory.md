# PauseHammer: Theory Sheet

A Windows tool to suspend ("pause") and resume processes using hotkeys. This guide covers the theory behind all major components.

---

## 1. Windows Processes & Threads

### Concepts
- A process is a running instance of a program.
- Has its own virtual memory, handles, and resources.
- Each process has a Process ID (PID).

### Threads
- Threads are units of execution within a process.
- All threads in a process share memory.
- Suspending all threads effectively "freezes" a process.

### Key APIs
- CreateToolhelp32Snapshot — take a snapshot of processes/threads.
- Process32First / Process32Next — iterate through processes.
- Thread32First / Thread32Next — iterate through threads.
- OpenProcess — get a handle to a process.
- OpenThread — get a handle to a thread.
- SuspendThread / ResumeThread — control thread execution.

---

## 2. Hotkeys & Message Loop

### Message Loop
- Windows programs use message loops to process events.
- Essential for receiving WM_HOTKEY messages.
```cpp
MSG msg;
while (GetMessage(&msg, NULL, 0, 0)) {
    if (msg.message == WM_HOTKEY) {
        // Handle hotkey
    }
}
```

### Registering Global Hotkeys
- RegisterHotKey(NULL, id, MOD_ALT | MOD_CONTROL, 'P');
- Requires a message loop to function.
- Unique id identifies the hotkey.

### Notes
- Only one process can register a given key combo at a time.
- Must call UnregisterHotKey on shutdown.

---

## 3. Thread Enumeration & Suspension

### Why Threads?
- There's no direct API to pause a whole process.
- Suspending all threads achieves the same effect.

### Steps
1. Get process ID (via name or PID).
2. Use CreateToolhelp32Snapshot to find all threads.
3. Filter by th32OwnerProcessID.
4. Open each thread with OpenThread.
5. Call SuspendThread(handle) to pause, ResumeThread(handle) to unpause.

### Caveats
- Some threads (especially system or protected) may fail to suspend.
- Improper resuming can crash the process.

---

## 4. Logging Actions

### Why Logging?
- Trace errors, understand what the tool is doing.
- Essential for debugging and visibility.

### What to Log
- Process found/not found.
- Thread suspend/resume status.
- Errors (e.g., permission denied).
- Current pause state.

### Log Destinations
- Console (std::cout)
- Optional: File output using ofstream

---

## 5. Hotkey-Based Control

### Goal
- Toggle pause/unpause state with a key press.

### State Handling
- Maintain bool isPaused = false;
- On hotkey press:
```cpp
if (!isPaused) suspendAll(); else resumeAll();
isPaused = !isPaused;
```

### Tips
- Prevent rapid toggles with cooldowns.
- Add feedback via console/logs.

---

## 6. Project Structure & CMake

### Why CMake?
- Cross-platform, IDE-friendly build system.
- Helps manage source files and build settings cleanly.

### Suggested Structure
```
PauseHammer/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── process_utils.cpp/.h
│   ├── thread_manager.cpp/.h
│   ├── hotkey_handler.cpp/.h
│   └── logger.cpp/.h
└── include/ (optional for public headers)
```

### CMake Basics
```cmake
cmake_minimum_required(VERSION 3.16)
project(PauseHammer)

set(CMAKE_CXX_STANDARD 17)

add_executable(PauseHammer
    src/main.cpp
    src/process_utils.cpp
    src/thread_manager.cpp
    src/hotkey_handler.cpp
    src/logger.cpp
)
```

---

## References & Resources

- Windows Internals by Mark Russinovich
- MSDN: ToolHelp APIs, SuspendThread, OpenThread, RegisterHotKey
- https://learn.microsoft.com/en-us/windows/win32/api/
- https://cmake.org/cmake/help/latest/guide/tutorial/
