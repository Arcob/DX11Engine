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
// HR宏
// ------------------------------
// Debug模式下的错误提醒与追踪
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)												\
	{															\
		long hr = (x);										\
		if(FAILED(hr))											\
		{														\
			print("Error HR");\
		}														\
	}
#endif
#else
#ifndef HR
#define HR(x) (x)
#endif 
#endif

#if defined(DEBUG) | defined(_DEBUG)
#ifndef FL
#define FL(x)												\
	{															\
		bool flag = (x);										\
		if(!(flag))											\
		{														\
			print("Error FL");\
		}														\
	}
#endif
#else
#ifndef FL
#define FL(x) (x)
#endif 
#endif