#include "RacingGameAssets.h"
#include "RacingGameApplication.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcScene.h"
#include "ArcMath.h"

RacingGameApplication::RacingGameApplication(unsigned int WIDTH, unsigned int HEIGHT, std::shared_ptr<DX11Engine::ArcAssets> assets) : ArcApplication(WIDTH, HEIGHT, assets) {
	ArcApplication::SetName("RacingGameApplication");
	ArcApplication::m_sceneList = {};
	ArcApplication::m_mainScene = nullptr;
	RacingGameApplication::LoadApplication();
}

void RacingGameApplication::LoadApplication() {
	auto mainScene = std::make_shared<DX11Engine::ArcScene>("Main Scene");
	m_sceneList.push_back(mainScene);
	ArcApplication::m_mainScene = mainScene;

	auto testBox = std::make_shared<DX11Engine::ArcGameObject>("TestBox");
	auto testBoxTransform = std::make_shared<DX11Engine::ArcTransform>();
	testBoxTransform->setPosition(float3(0, 0, 0));
	testBoxTransform->setRotation(float3(0, 0, 0));
	testBoxTransform->setScale(float3(1, 1, 1));
	testBox->SetTransfrom(testBoxTransform);
	testBox->SetMesh(ArcApplication::m_assets->findMesh("Box Mesh"));
	testBox->SetMaterial(ArcApplication::m_assets->findMaterial("SimpleMaterial"));
	ArcApplication::m_mainScene->AddGameObject(testBox);
}