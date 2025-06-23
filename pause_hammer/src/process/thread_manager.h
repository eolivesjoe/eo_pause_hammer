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

		void togglePause();

	private:
		DWORD m_pid;
		bool m_isPaused;
		std::unordered_map<DWORD, int> m_suspendedThreads;

		void suspendAllThreads();

		void resumeAllThreads();

		void forEachThreadInProcess(const std::function<void(HANDLE, DWORD)>& action);
	};
} // namespace process