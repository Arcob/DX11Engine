#pragma once
#include "ArcApplication.h"
class DebugApplication :
	public DX11Engine::ArcApplication
{
public:
	DebugApplication(unsigned int WIDTH, unsigned int HEIGHT, std::shared_ptr<DX11Engine::ArcAssets> assets);
	void LoadApplication();

};

