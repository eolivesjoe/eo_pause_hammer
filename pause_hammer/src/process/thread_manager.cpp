#include "thread_manager.h"

namespace process {
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

	}

	// Resumes all threads in the process
	void ThreadManager::resumeAllThreads()
	{

	}

	void ThreadManager::forEachThreadInProcess(const std::function<void(HANDLE)>& action)
	{

	}
}