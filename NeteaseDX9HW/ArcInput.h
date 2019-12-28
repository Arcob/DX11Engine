#pragma once

#include "CommonHeaders.h"

class ArcWindows;

const int MAX_KEY_INDEX = 349; // GLFW_KEY_LAST

typedef void(*pInputCallback)(int);

class ArcInput
{
public:
	static bool getKeyDown(const int key);
	static bool getKey(const int key);
	static bool getKeyUp(const int key);
	static void setWindowAndKeyboardCallback(ArcWindows* window);
	//给你一个重载callback的机会
	static void setWindowAndKeyboardCallback(ArcWindows* window, pInputCallback callBack);
	static void clearCache();
	static void swapTwoArray(bool * cache, bool* origin, const int size);

private:
	static ArcWindows* m_window;
	static std::vector<int> _tempKeyPress;
	static std::vector<int> _tempKeyRelease;
	static std::vector<int> _tempKeyPressCache;  // 使用缓存让当前帧的按下情况缓存到下一帧
	static std::vector<int> _tempKeyReleaseCache;
	static bool _downHash[MAX_KEY_INDEX + 1];  // 静态数组
	static bool _downHashCache[MAX_KEY_INDEX + 1];  // 静态数组

	static void key_callback(ArcWindows* window, int key, int scancode, int action, int mods);
};



