#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <functional>
#include <unordered_map>

namespace process 
{

	class ThreadManager
	{
	public:
		ThreadManager(DWORD pid);

		// Toggles between suspending and resuming all threads
		void togglePause();

	private:
		DWORD m_pid;
		bool m_isPaused;
		std::unordered_map<DWORD, int> m_suspendedThreads;

		void suspendAllThreads();

		// Resumes all threads in the process
		void resumeAllThreads();

		// Applies a function to all threads in the process
		void forEachThreadInProcess(const std::function<void(HANDLE)>& action);
	};
} // namespace process