#include "CommonHeaders.h"
#include "RacingGameAssets.h"
#include "DebugApplication.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcScene.h"
#include "ArcMath.h"
#include "ArcBehaviour.h"
#include "ArcCamera.h"
#include "Light.h"
#include "DebugCameraMove.h"
#include "SkyboxFollowCamera.h"

DebugApplication::DebugApplication(unsigned int WIDTH, unsigned int HEIGHT, std::shared_ptr<DX11Engine::ArcAssets> assets) : ArcApplication(WIDTH, HEIGHT, assets) {
	ArcApplication::SetName("DebugApplication");
	ArcApplication::m_sceneList = {};
	ArcApplication::m_mainScene = nullptr;
	DebugApplication::LoadApplication();
}

void DebugApplication::LoadApplication() {
	auto mainScene = std::make_shared<DX11Engine::ArcScene>("Main Scene");
	m_sceneList.push_back(mainScene);
	ArcApplication::m_mainScene = mainScene;

	auto mainCameraGameObject = std::make_shared<DX11Engine::ArcGameObject>("Camera");
	DX11Engine::ArcGameObject::RegisterGameObject(mainCameraGameObject);
	auto mainCameraTransform = std::make_shared<DX11Engine::ArcTransform>();
	mainCameraTransform->SetLocalPosition(float3(-1.6f, 7.f, 1.f));
	mainCameraTransform->SetLocalRotation(float3(0.f, 45.f, 0.f));
	//mainCameraTransform->SetLocalScale(float3(2.0f, 2.0f, 2.0f));
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
	directionalLightTransform->SetLocalPosition(float3(0.f, 3.f, 0.f));
	directionalLightTransform->SetLocalRotation(float3(50.0f, -30.0f, 0.0f));
	directionalLightTransform->SetLocalScale(float3(1.0f, 1.0f, 1.0f));
	directionalLightGameObject->SetTransfrom(directionalLightTransform);
	float lightIntensity = 0.5f;
	float4 lightColor = float4(1.f, 0.96f, 0.84f, 1.f);
	float4 lightOrthoPara = float4(Width(), Height(), 0.3f, 100.0f);
	auto directionalLight = std::make_shared<DX11Engine::DirectionalLight>(lightIntensity, lightColor, lightOrthoPara);
	directionalLightGameObject->AttachScript(directionalLight);
	MainScene()->SetMainLight(std::move(directionalLight));
	MainScene()->AddGameObject(directionalLightGameObject);
	
	auto skyBox = std::make_shared<DX11Engine::ArcGameObject>("SkyBox");
	DX11Engine::ArcGameObject::RegisterGameObject(skyBox);
	auto tempSkyBoxTransform = std::make_shared<DX11Engine::ArcTransform>();
	tempSkyBoxTransform->SetLocalPosition(float3(0.f, 0.f, 0.f));
	//tempSkyBoxTransform->SetPosition(float3(0.f, 0.f, 0.f));
	tempSkyBoxTransform->SetLocalRotation(float3(0, 0, 0));
	
	//DX11Engine::ArcTransform::SetParent(tempSkyBoxTransform, mainCameraTransform);
	skyBox->SetTransfrom(tempSkyBoxTransform);
	skyBox->SetMesh(ArcApplication::m_assets->findMesh("Sphere Mesh"));
	skyBox->SetMaterial(ArcApplication::m_assets->findMaterial("SkyBoxMaterial"));
	auto followCameraScript = std::make_shared<SkyboxFollowCamera>();
	skyBox->AttachScript(followCameraScript);
	MainScene()->AddGameObject(skyBox);

	auto testBox = std::make_shared<DX11Engine::ArcGameObject>("TestBox");
	DX11Engine::ArcGameObject::RegisterGameObject(testBox);
	auto testBoxTransform = std::make_shared<DX11Engine::ArcTransform>();
	testBox->SetTransfrom(testBoxTransform);
	DX11Engine::ArcTransform::SetParent(testBoxTransform, mainCameraTransform);
	testBoxTransform->SetPosition(float3(2.0f, 7.0f, 6.0f));
	testBoxTransform->SetRotation(float3(45.0f, 45.0f, 45.0f));
	testBoxTransform->SetScale(float3(1, 1, 1));
	testBox->SetMesh(ArcApplication::m_assets->findMesh("Box Mesh"));
	testBox->SetMaterial(ArcApplication::m_assets->findMaterial("TestBoxMaterial"));
	MainScene()->AddGameObject(testBox);

	auto testBoxWithNormal = std::make_shared<DX11Engine::ArcGameObject>("TestBoxWithNormal");
	DX11Engine::ArcGameObject::RegisterGameObject(testBoxWithNormal);
	auto testBoxTransform2 = std::make_shared<DX11Engine::ArcTransform>();
	testBoxTransform2->SetLocalPosition(float3(4.0f, 7.0f, 6.0f));
	testBoxTransform2->SetLocalRotation(float3(45.0f, 45.0f, 45.0f));
	testBoxTransform2->SetLocalScale(float3(2, 2, 2));
	testBoxWithNormal->SetTransfrom(testBoxTransform2);
	testBoxWithNormal->SetMesh(ArcApplication::m_assets->findMesh("Generated Box Mesh"));
	testBoxWithNormal->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	MainScene()->AddGameObject(testBoxWithNormal);

	auto cylinder = std::make_shared<DX11Engine::ArcGameObject>("Cylinder");
	DX11Engine::ArcGameObject::RegisterGameObject(cylinder);
	auto cylinderTransform = std::make_shared<DX11Engine::ArcTransform>();
	cylinderTransform->SetLocalPosition(float3(0.0f, 7.0f, 6.0f));
	cylinderTransform->SetLocalRotation(float3(0.0f, 0.0f, 0.0f));
	//cylinderTransform->SetLocalScale(float3(0.01f, 0.01f, 0.01f));
	cylinderTransform->SetLocalScale(float3(1.f, 1.f, 1.f));
	cylinder->SetTransfrom(cylinderTransform);
	cylinder->SetMesh(ArcApplication::m_assets->findMesh("Cylinder Mesh"));
	cylinder->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	MainScene()->AddGameObject(cylinder);

	auto cat= std::make_shared<DX11Engine::ArcGameObject>("Cat");
	DX11Engine::ArcGameObject::RegisterGameObject(cat);
	auto catTransform = std::make_shared<DX11Engine::ArcTransform>();
	catTransform->SetLocalPosition(float3(0.0f, 7.0f, 6.0f));
	catTransform->SetLocalRotation(float3(0.0f, 0.0f, 0.0f));
	catTransform->SetLocalScale(float3(0.003f, 0.003f, 0.003f));
	cat->SetTransfrom(catTransform);
	//cat->SetMesh(ArcApplication::m_assets->findMesh("Cat Mesh"));
	//cat->SetMaterial(ArcApplication::m_assets->findMaterial("CatMaterial"));
	MainScene()->AddGameObject(cat);/**/
}