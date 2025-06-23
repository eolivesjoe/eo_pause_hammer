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

		forEachThreadInProcess([this](HANDLE hThread)
			{
				DWORD tid = GetThreadId(hThread);
				SuspendThread(hThread);

				if (SuspendThread(hThread) != (DWORD) - 1)
				{
					m_suspendedThreads[tid]++;
				}
				else
				{
					logger::error("Suspend thread: " + tid);
				}
			});
	}

	// Resumes all threads in the process
	void ThreadManager::resumeAllThreads()
	{
		forEachThreadInProcess([](HANDLE hThread)
			{
				ResumeThread(hThread);
			});
	}

	void ThreadManager::forEachThreadInProcess(const std::function<void(HANDLE)>& action)
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
						action(hThread);
						CloseHandle(hThread);
					}
				}
			} while (Thread32Next(snapshot, &entry));
		}

		CloseHandle(snapshot);
	}
}