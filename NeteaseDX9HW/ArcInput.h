#pragma once

#include "CommonHeaders.h"
#include "ArcWindow.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace DX11Engine {

	const int MAX_KEY_INDEX = 349; // GLFW_KEY_LAST

	typedef void(*pInputCallback)(int);

	class ArcInput
	{
	public:
		static bool Init();
		static bool getKeyDown(const int key);
		static bool getKey(const int key);
		static bool getKeyUp(const int key);
		static void setWindowAndKeyboardCallback(ArcWindow* window);
		//����һ������callback�Ļ���
		static void setWindowAndKeyboardCallback(ArcWindow* window, pInputCallback callBack);
		static void clearCache();
		static void swapTwoArray(bool * cache, bool* origin, const int size);

	private:
		static ArcWindow* m_window;
		static std::unique_ptr<DirectX::Mouse> m_ArcMouse;
		static std::unique_ptr<DirectX::Keyboard> m_ArcKeyboard;
		static bool m_inited;
		static std::vector<int> m_tempKeyPress;
		static std::vector<int> m_tempKeyRelease;
		static std::vector<int> m_tempKeyPressCache;  // ʹ�û����õ�ǰ֡�İ���������浽��һ֡
		static std::vector<int> m_tempKeyReleaseCache;
		static bool m_downHash[MAX_KEY_INDEX + 1];  // ��̬����
		static bool m_downHashCache[MAX_KEY_INDEX + 1];  // ��̬����

		static void key_callback(ArcWindow* window, int key, int scancode, int action, int mods);
	};

}

