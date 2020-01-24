#pragma once

#include "CommonHeaders.h"
#include "ArcWindow.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ArcMath.h"

namespace DX11Engine {

	enum MouseKey {
		LeftClick = 0,
		RightClick = 1,
		ScrollWheel = 2,
		Max = 3
	};

	const int MAX_KEY_INDEX = 349; // GLFW_KEY_LAST

	typedef void(*pInputCallback)(int);

	class ArcInput
	{
	public:
		static bool Init(std::shared_ptr<ArcWindow> window);
		static void Update();
		static float2 GetMouseDelta();
		static bool getKeyDown(const int key);
		static bool getKeyboardKey(const int key);
		static bool getMouseKey(MouseKey key);
		static float2 GetMousePos();
		static bool getKeyUp(const int key);
		static void setWindowAndKeyboardCallback(ArcWindow* window);
		//给你一个重载callback的机会
		static void setWindowAndKeyboardCallback(ArcWindow* window, pInputCallback callBack);
		static void clearCache();
		static void swapTwoArray(bool * cache, bool* origin, const int size);

		static DirectX::Mouse::State mouseState;
		static DirectX::Mouse::State lastMouseState;
		static DirectX::Keyboard::State keyState;
		static DirectX::Keyboard::State lastKeyState;

	private:
		static std::shared_ptr<ArcWindow> m_window;
		static std::shared_ptr<DirectX::Mouse> m_pMouse;
		static std::shared_ptr<DirectX::Keyboard> m_pKeyboard;
		static DirectX::Mouse::ButtonStateTracker m_MouseTracker;
		static DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;
		static bool m_inited;
		static std::vector<int> m_tempKeyPress;
		static std::vector<int> m_tempKeyRelease;
		static std::vector<int> m_tempKeyPressCache;  // 使用缓存让当前帧的按下情况缓存到下一帧
		static std::vector<int> m_tempKeyReleaseCache;
		static bool m_downHash[MAX_KEY_INDEX + 1];  // 静态数组
		static bool m_downHashCache[MAX_KEY_INDEX + 1];  // 静态数组

		static void key_callback(ArcWindow* window, int key, int scancode, int action, int mods);
	};

}

