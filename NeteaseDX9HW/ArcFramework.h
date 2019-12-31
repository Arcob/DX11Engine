#pragma once

#include "CommonHeaders.h"

namespace DX11Engine {

	class ArcFramework //跨平台强相关
	{
	public:
		static int init();
		static std::shared_ptr<class ArcWindow> showWindows(std::string name, int height, int width);
		static void configInput(int height, int width);
		static time_t getTime();//应用运行的毫秒数
		static void termiate();

	private:
		static time_t initTime;
	};
}



