#pragma once

#include <string>
#include <windows.h>

namespace DX11Engine {

	class ArcWindow
	{
	public:
		ArcWindow(std::string name, int width, int height);
		~ArcWindow() = default;
		size_t GetHandle();
		bool DX11createWindow();
		void TreatMessage(bool &isRunning);
		LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	private:
		size_t m_handle;
		std::string m_name;
		bool escPushed;
		int m_width;
		int m_height;
		MSG m_msg;
		HINSTANCE m_hinstance;
	};
}

