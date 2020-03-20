#pragma once
#include "ArcApplication.h"
class ShadowApplication :
	public DX11Engine::ArcApplication
{
public:
	ShadowApplication(unsigned int WIDTH, unsigned int HEIGHT, std::shared_ptr<DX11Engine::ArcAssets> assets);
	void LoadApplication();
};

