#pragma once
#include "ArcApplication.h"
class RacingGameApplication :
	public DX11Engine::ArcApplication
{
public:
	RacingGameApplication(unsigned int WIDTH, unsigned int HEIGHT, std::shared_ptr<DX11Engine::ArcAssets> assets);
	void LoadApplication();

};