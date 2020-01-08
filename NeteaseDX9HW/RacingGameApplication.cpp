#include "CommonHeaders.h"
#include "RacingGameAssets.h"
#include "RacingGameApplication.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcScene.h"
#include "ArcMath.h"
#include "ArcBehaviour.h"
#include "ArcCamera.h"

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

	auto mainCameraGameObject = std::make_shared<DX11Engine::ArcGameObject>("Camera");
	auto tempTransform = std::make_shared<DX11Engine::ArcTransform>();
	tempTransform->setPosition(float3(2.5, 7, 1));
	tempTransform->setRotation(float3(75, 180, 0));
	auto mainCamera = std::make_shared<DX11Engine::ArcCamera>();
	mainCamera->SetViewportAspectRatio(ArcApplication::Width() / ArcApplication::Height());
	mainCameraGameObject->SetTransfrom(tempTransform);
	mainCameraGameObject->AttachScript(mainCamera);
	MainScene()->SetMainCamera(mainCamera);
	//auto gameController = std::make_shared<GameController>();
	//tempGameObject0->attachScript(gameController);
	MainScene()->AddGameObject(mainCameraGameObject);

	auto testBox = std::make_shared<DX11Engine::ArcGameObject>("TestBox");
	auto testBoxTransform = std::make_shared<DX11Engine::ArcTransform>();
	testBoxTransform->setPosition(float3(0.5f, 0, 0.5f));
	testBoxTransform->setRotation(float3(0, 0, 0));
	testBoxTransform->setScale(float3(1, 1, 1));
	testBox->SetTransfrom(testBoxTransform);
	testBox->SetMesh(ArcApplication::m_assets->findMesh("Box Mesh"));
	testBox->SetMaterial(ArcApplication::m_assets->findMaterial("TestBoxMaterial"));
	ArcApplication::m_mainScene->AddGameObject(testBox);
}