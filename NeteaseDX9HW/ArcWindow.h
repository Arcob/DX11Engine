#pragma once

#include <string>
#include <windows.h>
#include "Keyboard.h"
#include "Mouse.h"

namespace DX11Engine {

	class ArcWindow
	{
	public:
		ArcWindow(std::string name, int width, int height);
		~ArcWindow() = default;
		size_t GetHandle();
		bool DX11createWindow();
		void TreatMessage(bool &isRunning);
		void SetMouseAndKeyboard(std::shared_ptr<DirectX::Mouse> mouse, std::shared_ptr<DirectX::Keyboard> keyboard);
		LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	private:
		size_t m_handle;
		std::string m_name;
		bool escPushed;
		int m_width;
		int m_height;
		MSG m_msg;
		HINSTANCE m_hinstance;
		std::shared_ptr<DirectX::Mouse> m_pMouse;
		std::shared_ptr<DirectX::Keyboard> m_pKeyboard;
	};
}

