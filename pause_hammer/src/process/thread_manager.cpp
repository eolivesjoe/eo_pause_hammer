#include "thread_manager.h"
#include "../logger/logger.h"

namespace process 
{
	ThreadManager::ThreadManager(DWORD pid)
	{
		this->m_pid = pid;
		this->m_isPaused = false;
	}

	void ThreadManager::togglePause()
	{
		if (m_isPaused == true)
		{
			resumeAllThreads();
			m_isPaused = false;
		}
		else
		{
			suspendAllThreads();
			m_isPaused = true;
		}
	}

	void ThreadManager::suspendAllThreads()
	{
		m_suspendedThreads.clear();
		logger::info("SUSPENDING");
		forEachThreadInProcess([this](HANDLE hThread, DWORD threadId)
			{
				auto threadSuspendCount = SuspendThread(hThread);
				logger::info(threadId);

				if (threadSuspendCount != (DWORD)-1)
				{
					++m_suspendedThreads[threadId];
				}
				else
				{
					logger::error(threadId);
				}
			});
	}

	void ThreadManager::resumeAllThreads()
	{
		logger::info("RESUMING");
		for (const auto& [threadId, count] : m_suspendedThreads)
		{
			HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
			if (hThread != nullptr)
			{
				for (int i = 0; i != count; ++i)
				{
					auto threadSuspendCount = ResumeThread(hThread);
					logger::info(threadId);
					if (threadSuspendCount == (DWORD)-1)
					{
						logger::error(threadId);
					}
				}
				CloseHandle(hThread);
			}
			else
			{
				logger::error("OpenThread Failed");
				logger::error(threadId);
			}
		}
	}

	void ThreadManager::forEachThreadInProcess(const std::function<void(HANDLE, DWORD)>& action)
	{
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
						action(hThread, entry.th32ThreadID);
						CloseHandle(hThread);
					}
				}
			} while (Thread32Next(snapshot, &entry));
		}

		CloseHandle(snapshot);
	}
}