#include "ArcInput.h"
#include "DriverSetting.h"

namespace DX11Engine {

	std::shared_ptr<ArcWindow> ArcInput::m_window = nullptr;
	std::vector<int> ArcInput::m_tempKeyPress = std::vector<int>();
	std::vector<int> ArcInput::m_tempKeyRelease = std::vector<int>();
	std::vector<int> ArcInput::m_tempKeyPressCache = std::vector<int>();
	std::vector<int> ArcInput::m_tempKeyReleaseCache = std::vector<int>();
	std::shared_ptr<DirectX::Mouse> ArcInput::m_pMouse = nullptr;
	std::shared_ptr<DirectX::Keyboard> ArcInput::m_pKeyboard = nullptr;
	DirectX::Mouse::State ArcInput::mouseState;
	DirectX::Mouse::State ArcInput::lastMouseState;
	DirectX::Keyboard::State ArcInput::keyState;
	DirectX::Keyboard::State ArcInput::lastKeyState;
	DirectX::Mouse::ButtonStateTracker ArcInput::m_MouseTracker;
	DirectX::Keyboard::KeyboardStateTracker ArcInput::m_KeyboardTracker;
	bool ArcInput::m_downHash[] = { false };
	bool ArcInput::m_downHashCache[] = { false };

	bool ArcInput::Init(std::shared_ptr<ArcWindow> window) {
		m_window = window;
		m_pMouse = std::make_unique<DirectX::Mouse>();
		m_pKeyboard = std::make_unique<DirectX::Keyboard>();
		// 初始化鼠标，键盘不需要
		m_pMouse->SetWindow((HWND)(m_window->GetHandle()));
		m_pMouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);

		m_window->SetMouseAndKeyboard(m_pMouse, m_pKeyboard);
		return true;
	}

	void ArcInput::Update() {
		//print(m_Mouse->GetState().x);
		// 获取鼠标状态
		mouseState = m_pMouse->GetState();
		lastMouseState = m_MouseTracker.GetLastState();
		// 获取键盘状态
		keyState = m_pKeyboard->GetState();
		lastKeyState = m_KeyboardTracker.GetLastState();

		// 更新鼠标按钮状态跟踪器，仅当鼠标按住的情况下才进行移动
		m_MouseTracker.Update(mouseState);
		m_KeyboardTracker.Update(keyState);

	}

	float2 ArcInput::GetMouseDelta() {
		return float2((mouseState.x - lastMouseState.x) / ((float)WIDTH), (mouseState.y - lastMouseState.y) / ((float)HEIGHT));
	}

	float2 ArcInput::GetMousePos() {
		return float2(mouseState.x /((float)WIDTH), mouseState.y / ((float)HEIGHT));
	}
	/*
	void ArcInput::setWindowAndKeyboardCallback(ArcWindows* window) {
		m_window = window;
		glfwSetKeyCallback(_window, key_callback);
	}

	void ArcInput::setWindowAndKeyboardCallback(ArcWindows* window, pInputCallback callBack) {
		m_window = window;
		glfwSetKeyCallback(_window, callBack);
	}

	void ArcInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//std::cout << key << std::endl;
		if (action == GLFW_PRESS) {
			_tempKeyPress.push_back(key);
			ArcInput::_downHash[key] = true;
		}
		if (action == GLFW_RELEASE) {
			_tempKeyRelease.push_back(key);
			ArcInput::_downHash[key] = false;
		}
	}
	*/

	void ArcInput::clearCache() {
		//swapTwoArray(_downHashCache, _downHash, GLFW_KEY_LAST + 1);
		memcpy(m_downHashCache, m_downHash, (MAX_KEY_INDEX + 1));
		m_tempKeyPressCache.swap(m_tempKeyPress);
		m_tempKeyReleaseCache.swap(m_tempKeyRelease);
		m_tempKeyPress.clear();
		m_tempKeyRelease.clear();
	}

	bool ArcInput::GetKeyDown(const int key) {
		for (int i = 0; i < m_tempKeyPressCache.size(); i++) {
			if (m_tempKeyPressCache[i] == key) {
				return true;
			}
		}
		return false;
	}

	bool ArcInput::GetKeyboardKey(const int key) {
		return keyState.IsKeyDown((DirectX::Keyboard::Keys)key);
	}

	bool ArcInput::GetKeyboardKeyDown(const int key) {
		return (keyState.IsKeyDown((DirectX::Keyboard::Keys)key) && !lastKeyState.IsKeyDown((DirectX::Keyboard::Keys)key));
	}

	bool ArcInput::GetKeyboardKeyUp(const int key) {
		return (!keyState.IsKeyDown((DirectX::Keyboard::Keys)key) && lastKeyState.IsKeyDown((DirectX::Keyboard::Keys)key));
	}

	bool ArcInput::GetMouseKey(MouseKey key) {
		if (key == MouseKey::LeftClick) {
			return mouseState.leftButton;
		}
		else if (key == MouseKey::RightClick) 
		{
			return mouseState.rightButton;
		}
		else if (key == MouseKey::ScrollWheel) {
			return mouseState.middleButton;
		}
		return false;
	}

	bool ArcInput::GetKeyUp(const int key) {
		for (int i = 0; i < m_tempKeyReleaseCache.size(); i++) {
			if (m_tempKeyReleaseCache[i] == key) {
				return true;
			}
		}
		return false;
	}

	void ArcInput::SwapTwoArray(bool * cache, bool* origin, const int size) {
		for (int i = 0; i < size; i++) {
			cache[i] = origin[i];
		}
	}

	float ArcInput::GetMouseScrollWheel() {
		return (mouseState.scrollWheelValue - lastMouseState.scrollWheelValue)/100.f;
	}
}