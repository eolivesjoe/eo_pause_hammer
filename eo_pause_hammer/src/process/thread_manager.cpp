#include "thread_manager.h"
#include "../logger/logger.h"

namespace process
{
	ThreadManager::ThreadManager(DWORD pid)
	{
		this->m_pid = pid;
		this->m_isPaused = false;
	}

	void ThreadManager::TogglePause()
	{
		if (m_isPaused == true)
		{
			ResumeAllThreads();
			m_isPaused = false;
		}
		else
		{
			SuspendAllThreads();
			m_isPaused = true;
		}
	}

	void ThreadManager::SuspendAllThreads()
	{
		logger::Info("pausing...");
		m_suspendedThreads.clear();

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (snapshot == INVALID_HANDLE_VALUE)
		{
			return;
		}

		THREADENTRY32 entry;
		entry.dwSize = sizeof(THREADENTRY32);

		if (Thread32First(snapshot, &entry))
		{
			do
			{
				if (entry.th32OwnerProcessID == m_pid)
				{
					HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, entry.th32ThreadID);
					if (hThread)
					{
						auto threadSuspendCount = SuspendThread(hThread);

						if (threadSuspendCount != (DWORD)-1)
						{
							++m_suspendedThreads[entry.th32ThreadID];
						}
						else
						{
							logger::Error(entry.th32ThreadID);
						}
						CloseHandle(hThread);
					}
				}
			} while (Thread32Next(snapshot, &entry));
		}
		CloseHandle(snapshot);
	}

	void ThreadManager::ResumeAllThreads()
	{
		logger::Info("resuming...");
		for (const auto& [threadId, count] : m_suspendedThreads)
		{
			HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
			if (hThread != nullptr)
			{
				for (int i = 0; i != count; ++i)
				{
					auto threadSuspendCount = ResumeThread(hThread);

					if (threadSuspendCount == (DWORD)-1)
					{
						logger::Error(threadId);
					}
				}
				CloseHandle(hThread);
			}
			else
			{
				logger::Error("OpenThread Failed");
				logger::Error(threadId);
			}
		}
	}
}