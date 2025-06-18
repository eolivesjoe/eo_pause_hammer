#pragma once

class ThreadManager;

namespace hotkeys {

	class Handler
	{
	public:
		Handler(ThreadManager& manager);

		void listener();

	private:
		ThreadManager& m_manager;
	};
} // namespace hotkeys