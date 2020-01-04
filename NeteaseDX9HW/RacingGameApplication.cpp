#include "RacingGameApplication.h"

RacingGameApplication::RacingGameApplication(unsigned int WIDTH, unsigned int HEIGHT) : ArcApplication(WIDTH, HEIGHT) {
	ArcApplication::SetName("RacingGameApplication");
	ArcApplication::m_sceneList = {};
	ArcApplication::m_mainScene = nullptr;
	RacingGameApplication::LoadScene();
}

void RacingGameApplication::LoadScene() {

}