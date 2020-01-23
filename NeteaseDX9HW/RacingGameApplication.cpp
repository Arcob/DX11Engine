#include "CommonHeaders.h"
#include "RacingGameAssets.h"
#include "RacingGameApplication.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcScene.h"
#include "ArcMath.h"
#include "ArcBehaviour.h"
#include "ArcCamera.h"
#include "Light.h"

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
	tempTransform->SetLocalPosition(float3(2.5f, 7.f, 1.f));
	tempTransform->SetLocalRotation(float3(-10.f, 10.f, 2.f));
	//tempTransform->SetLocalScale(float3(2.f, 2.f, 2.f));
	auto mainCamera = std::make_shared<DX11Engine::ArcCamera>();
	mainCamera->SetViewportAspectRatio(((float)ArcApplication::Width()) / ((float)ArcApplication::Height()));
	mainCameraGameObject->SetTransfrom(tempTransform);
	mainCameraGameObject->AttachScript(mainCamera);
	MainScene()->SetMainCamera(mainCamera);
	MainScene()->AddGameObject(mainCameraGameObject);

	auto directionalLight = std::make_shared<DX11Engine::DirectionalLight>(float3(0.5f, 0.5f, 0.5f), 1.0f, float4(1.f, 1.f, 0.f, 1.f));
	MainScene()->SetMainLight(std::move(directionalLight));

	auto skyBox = std::make_shared<DX11Engine::ArcGameObject>("SkyBox");
	auto tempSkyBoxTransform = std::make_shared<DX11Engine::ArcTransform>();
	tempSkyBoxTransform->SetLocalPosition(float3(0.f, 0.f, 0.f));
	tempSkyBoxTransform->SetLocalRotation(float3(0, 0, 0));
	DX11Engine::ArcTransform::SetParent(tempSkyBoxTransform, tempTransform);
	skyBox->SetTransfrom(tempSkyBoxTransform);
	skyBox->SetMesh(ArcApplication::m_assets->findMesh("Normal Box Mesh"));
	skyBox->SetMaterial(ArcApplication::m_assets->findMaterial("SkyBoxMaterial"));
	MainScene()->AddGameObject(skyBox);
	//print(tempSkyBoxTransform->Position().x << " " << tempSkyBoxTransform->Position().y << " " << tempSkyBoxTransform->Position().z);

	auto testBox = std::make_shared<DX11Engine::ArcGameObject>("TestBox");
	auto testBoxTransform = std::make_shared<DX11Engine::ArcTransform>();
	testBoxTransform->SetLocalPosition(float3(2.0f, 7.0f, 6.0f));
	testBoxTransform->SetLocalRotation(float3(45.0f, 45.0f, 45.0f));
	testBoxTransform->SetLocalScale(float3(1, 1, 1));
	testBox->SetTransfrom(testBoxTransform);
	testBox->SetMesh(ArcApplication::m_assets->findMesh("Box Mesh"));
	testBox->SetMaterial(ArcApplication::m_assets->findMaterial("TestBoxMaterial"));
	MainScene()->AddGameObject(testBox);

	auto testBoxWithNormal = std::make_shared<DX11Engine::ArcGameObject>("TestBoxWithNormal");
	auto testBoxTransform2 = std::make_shared<DX11Engine::ArcTransform>();
	testBoxTransform2->SetLocalPosition(float3(4.0f, 7.0f, 6.0f));
	testBoxTransform2->SetLocalRotation(float3(45.0f, 45.0f, 45.0f));
	testBoxTransform2->SetLocalScale(float3(1, 1, 1));
	testBoxWithNormal->SetTransfrom(testBoxTransform2);
	testBoxWithNormal->SetMesh(ArcApplication::m_assets->findMesh("Normal Box Mesh"));
	testBoxWithNormal->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	MainScene()->AddGameObject(testBoxWithNormal);
}