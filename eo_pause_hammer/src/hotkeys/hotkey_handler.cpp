#include <windows.h>

#include "hotkey_handler.h"
#include "../logger/logger.h"

namespace hotkeys 
{
	Handler::Handler(process::ThreadManager& manager)
		: m_manager(manager)
	{

	}

	void Handler::Listener()
	{
		const int HOTKEY_ID_CTRL_P = 1;
		if (!RegisterHotKey(NULL, HOTKEY_ID_CTRL_P, MOD_CONTROL, 0x50))
		{
			logger::Error("Failed to register hotkey CTRL+P");
			return;
		}
		logger::Info("Hotkey listener running. Press CTRL+P...");

		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID_CTRL_P)
			{
				m_manager.TogglePause();
			}
		}

		UnregisterHotKey(NULL, HOTKEY_ID_CTRL_P);
	}
}