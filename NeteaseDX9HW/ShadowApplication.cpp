#include "CommonHeaders.h"
#include "ShadowApplication.h"
#include "ShadowAssets.h"
#include "RacingGameApplication.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcScene.h"
#include "ArcMath.h"
#include "ArcBehaviour.h"
#include "ArcCamera.h"
#include "Light.h"
#include "CameraController.h"
#include "ShadowCameraController.h"
#include "DebugCameraMove.h"

ShadowApplication::ShadowApplication(unsigned int WIDTH, unsigned int HEIGHT, std::shared_ptr<DX11Engine::ArcAssets> assets) : ArcApplication(WIDTH, HEIGHT, assets) {
	ArcApplication::SetName("CascadedShadowMapApplication");
	ArcApplication::m_sceneList = {};
	ArcApplication::m_mainScene = nullptr;
	ShadowApplication::LoadApplication();
}

void ShadowApplication::LoadApplication() {
	auto mainScene = std::make_shared<DX11Engine::ArcScene>("Main Scene");
	m_sceneList.push_back(mainScene);
	ArcApplication::m_mainScene = mainScene;

	auto mainCameraGameObject = std::make_shared<DX11Engine::ArcGameObject>("Camera");
	DX11Engine::ArcGameObject::RegisterGameObject(mainCameraGameObject);
	auto mainCameraTransform = std::make_shared<DX11Engine::ArcTransform>();
	mainCameraTransform->SetLocalPosition(float3(15.0f, 8.f, 15.f));
	mainCameraTransform->SetLocalRotation(float3(30.0f, 225.0f, 0.f));
	mainCameraTransform->SetLocalScale(float3(1.0f, 1.0f, 1.0f));
	auto mainCamera = std::make_shared<DX11Engine::ArcCamera>();
	mainCamera->SetViewportAspectRatio(((float)ArcApplication::Width()) / ((float)ArcApplication::Height()));
	mainCameraGameObject->SetTransfrom(mainCameraTransform);
	mainCameraGameObject->AttachScript(mainCamera);
	auto cameraMove = std::make_shared<DebugCameraMove>();
	mainCameraGameObject->AttachScript(cameraMove);
	MainScene()->SetMainCamera(mainCamera);
	MainScene()->AddGameObject(mainCameraGameObject);

	auto directionalLightGameObject = std::make_shared<DX11Engine::ArcGameObject>("Directional Light");
	DX11Engine::ArcGameObject::RegisterGameObject(directionalLightGameObject);
	auto directionalLightTransform = std::make_shared<DX11Engine::ArcTransform>();
	directionalLightTransform->SetLocalPosition(float3(-6.f, 20.f, -12.f));
	directionalLightTransform->SetLocalRotation(float3(50.0f, 30.0f, 0.0f));
	directionalLightTransform->SetLocalScale(float3(1.0f, 1.0f, 1.0f));
	directionalLightGameObject->SetTransfrom(directionalLightTransform);
	float lightIntensity = 1.0f;
	float4 lightColor = float4(1.f, 0.96f, 0.84f, 1.f);
	float4 lightOrthoPara = float4(50.f, 50.f, 0.3f, 100.0f);
	auto directionalLight = std::make_shared<DX11Engine::DirectionalLight>(lightIntensity, lightColor, lightOrthoPara);
	directionalLightGameObject->AttachScript(directionalLight);
	MainScene()->SetMainLight(std::move(directionalLight));
	auto shadowCameraController = std::make_shared<ShadowCameraController>();
	directionalLightGameObject->AttachScript(shadowCameraController);
	MainScene()->AddGameObject(directionalLightGameObject);

	auto ground = std::make_shared<DX11Engine::ArcGameObject>("Ground");
	DX11Engine::ArcGameObject::RegisterGameObject(ground);
	auto groundTransform = std::make_shared<DX11Engine::ArcTransform>();
	ground->SetTransfrom(groundTransform);
	groundTransform->SetPosition(float3(0.0f, -0.1f, 0.0f));
	groundTransform->SetRotation(float3(0.0f, 0.0f, 0.0f));
	groundTransform->SetScale(float3(30.0f, 0.2f, 30.0f));
	ground->SetMesh(ArcApplication::m_assets->findMesh("Generated Box Mesh"));
	ground->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	MainScene()->AddGameObject(ground);

	int index = 0;
	for (int x = 13.5f; x > -15.0f; x -= 3.0f) {
		for (int y = 13.5f; y > -15.0f; y -= 3.0f) {
			std::string tempName = "Cube" + std::to_string(++index);
			auto cube = std::make_shared<DX11Engine::ArcGameObject>(tempName);
			DX11Engine::ArcGameObject::RegisterGameObject(cube);
			auto cubeTransform = std::make_shared<DX11Engine::ArcTransform>();
			cube->SetTransfrom(cubeTransform);
			cubeTransform->SetPosition(float3(x, 0.5f, y));
			cubeTransform->SetRotation(float3(0.0f, 0.0f, 0.0f));
			cubeTransform->SetScale(float3(1.0f, 1.0f, 1.0f));
			cube->SetMesh(ArcApplication::m_assets->findMesh("Generated Box Mesh"));
			cube->SetMaterial(ArcApplication::m_assets->findMaterial("MarbleMaterial"));
			MainScene()->AddGameObject(cube);
		}
	}
}