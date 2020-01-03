#include "ArcTool.h"
#include <direct.h>

namespace DX11Engine {

	std::string ArcTool::m_currentPath = "";

	const LPCWSTR ArcTool::stringToLPCWSTR(const std::string orig)
	{
		size_t origsize = orig.length() + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
		mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

		return wcstring;
	}

	std::string ArcTool::getCurrentPath() {
		if (m_currentPath.compare("") == 0) {
			char buf[80];
			_getcwd(buf, sizeof(buf)); //将当前工作目录的绝对路径复制到参数buffer所指的内存空间中
			std::string path1 = std::string(buf);
			std::size_t found = path1.find_last_of("/\\");
			m_currentPath = path1.substr(0, found);
		}
		return m_currentPath;
	}
}