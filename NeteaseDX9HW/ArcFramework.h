#pragma once

#include "CommonHeaders.h"

class ArcFramework
{
public:
	static int init();
	static std::shared_ptr<class ArcWindow> showWindows(std::string name, int height, int width);
	static void configInput(int height, int width);
	static time_t getTime();//应用运行的秒数
	static void termiate();

private:
	static time_t initTime;
};

