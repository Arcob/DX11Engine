#include "ShadowApplication.h"

ShadowApplication::ShadowApplication(unsigned int WIDTH, unsigned int HEIGHT, std::shared_ptr<DX11Engine::ArcAssets> assets) : ArcApplication(WIDTH, HEIGHT, assets) {
	ArcApplication::SetName("CascadedShadowMapApplication");
	ArcApplication::m_sceneList = {};
	ArcApplication::m_mainScene = nullptr;
	ShadowApplication::LoadApplication();
}

void ShadowApplication::LoadApplication() {

}