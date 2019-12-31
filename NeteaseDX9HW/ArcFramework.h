#pragma once

#include "CommonHeaders.h"

namespace DX11Engine {

	class ArcFramework //��ƽ̨ǿ���
	{
	public:
		static int init();
		static std::shared_ptr<class ArcWindow> showWindows(std::string name, int height, int width);
		static void configInput(int height, int width);
		static time_t getTime();//Ӧ�����еĺ�����
		static void termiate();

	private:
		static time_t initTime;
	};
}



