#pragma once

#include "ArcWindow.h"

namespace DX11Engine {

	class ArcTool //��ƽ̨�޹�
	{
	public:
		const static LPCWSTR stringToLPCWSTR(const std::string orig);
		static std::string getCurrentPath();
	private:
		static std::string m_currentPath;
	};

}

