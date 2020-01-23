#include "ArcInput.h"

namespace DX11Engine {

	ArcWindow* ArcInput::m_window = nullptr;
	std::vector<int> ArcInput::m_tempKeyPress = std::vector<int>();
	std::vector<int> ArcInput::m_tempKeyRelease = std::vector<int>();
	std::vector<int> ArcInput::m_tempKeyPressCache = std::vector<int>();
	std::vector<int> ArcInput::m_tempKeyReleaseCache = std::vector<int>();
	std::unique_ptr<DirectX::Mouse> ArcInput::m_ArcMouse = nullptr;
	std::unique_ptr<DirectX::Keyboard> ArcInput::m_ArcKeyboard = nullptr;
	bool ArcInput::m_downHash[] = { false };
	bool ArcInput::m_downHashCache[] = { false };

	bool ArcInput::Init() {
		m_ArcMouse = std::make_unique<DirectX::Mouse>();
		m_ArcKeyboard = std::make_unique<DirectX::Keyboard>();

		// 初始化鼠标，键盘不需要
		m_ArcMouse->SetWindow((HWND)(m_window->GetHandle()));
		m_ArcMouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);

		return true;
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

	bool ArcInput::getKeyDown(const int key) {
		for (int i = 0; i < m_tempKeyPressCache.size(); i++) {
			if (m_tempKeyPressCache[i] == key) {
				return true;
			}
		}
		return false;
	}

	bool ArcInput::getKey(const int key) {
		/*for (int i = 0; i < _tempKeyRepeatCache.size(); i++) {
			if (_tempKeyRepeatCache[i] == key) {
				return true;
			}
		}
		return false;*/
		return ArcInput::m_downHashCache[key];
	}

	bool ArcInput::getKeyUp(const int key) {
		for (int i = 0; i < m_tempKeyReleaseCache.size(); i++) {
			if (m_tempKeyReleaseCache[i] == key) {
				return true;
			}
		}
		return false;
	}

	void ArcInput::swapTwoArray(bool * cache, bool* origin, const int size) {
		for (int i = 0; i < size; i++) {
			cache[i] = origin[i];
		}
	}
}