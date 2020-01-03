#pragma once

#include "ArcWindow.h"

namespace DX11Engine {

	class ArcTool //跨平台无关
	{
	public:
		const static LPCWSTR stringToLPCWSTR(const std::string orig);
		static std::string getCurrentPath();
	private:
		static std::string m_currentPath;
	};

}

