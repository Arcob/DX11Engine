#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <array>
#include <memory>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <list>
#include <streambuf>
#include <direct.h>
#include <typeinfo>
#include <time.h>
#include "DDSTextureLoader.h"

#define print(a) std::cout << a << std::endl

// ------------------------------
// HR��
// ------------------------------
// Debugģʽ�µĴ���������׷��
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)												\
	{															\
		HRESULT hr = (x);										\
		if(FAILED(hr))											\
		{														\
			DXTraceW(__FILEW__, (DWORD)__LINE__, hr, L#x, true);\
		}														\
	}
#endif
#else
#ifndef HR
#define HR(x) (x)
#endif 
#endif