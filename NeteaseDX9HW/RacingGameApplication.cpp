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
#include "CarMove.h"
#include "DebugCameraMove.h"
#include "SkyboxFollowCamera.h"
#include "CameraController.h"
#include "WheelMove.h"

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
	DX11Engine::ArcGameObject::RegisterGameObject(mainCameraGameObject);
	auto mainCameraTransform = std::make_shared<DX11Engine::ArcTransform>();
	mainCameraTransform->SetLocalPosition(float3(0.f, 1.f, -5.f));
	mainCameraTransform->SetLocalRotation(float3(0.f, 0.f, 0.f));
	mainCameraTransform->SetLocalScale(float3(1.0f, 1.0f, 1.0f));
	auto mainCamera = std::make_shared<DX11Engine::ArcCamera>();
	mainCamera->SetViewportAspectRatio(((float)ArcApplication::Width()) / ((float)ArcApplication::Height()));
	mainCameraGameObject->SetTransfrom(mainCameraTransform);
	mainCameraGameObject->AttachScript(mainCamera);
	auto cameraController = std::make_shared<CameraController>();
	mainCameraGameObject->AttachScript(cameraController);
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
	tempSkyBoxTransform->SetLocalRotation(float3(0, 0, 0));
	skyBox->SetTransfrom(tempSkyBoxTransform);
	skyBox->SetMesh(ArcApplication::m_assets->findMesh("Sphere Mesh"));
	skyBox->SetMaterial(ArcApplication::m_assets->findMaterial("SkyBoxMaterial"));
	auto followCameraScript = std::make_shared<SkyboxFollowCamera>();
	skyBox->AttachScript(followCameraScript);
	MainScene()->AddGameObject(skyBox);

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

	auto car = std::make_shared<DX11Engine::ArcGameObject>("Car");
	DX11Engine::ArcGameObject::RegisterGameObject(car);
	auto carTransform = std::make_shared<DX11Engine::ArcTransform>();
	car->SetTransfrom(carTransform);
	carTransform->SetPosition(float3(0.0f, 0.2f, 0.0f));
	carTransform->SetRotation(float3(0.0f, 0.0f, 0.0f));
	carTransform->SetScale(float3(1.0f, 1.0f, 1.0f));
	auto carMove = std::make_shared<CarMove>();
	car->AttachScript(carMove);
	MainScene()->AddGameObject(car);

	auto carBody = std::make_shared<DX11Engine::ArcGameObject>("CarBody");
	DX11Engine::ArcGameObject::RegisterGameObject(carBody);
	auto carBodyTransform = std::make_shared<DX11Engine::ArcTransform>();
	carBody->SetTransfrom(carBodyTransform);
	DX11Engine::ArcTransform::SetParent(carBodyTransform, carTransform);
	carBodyTransform->SetLocalPosition(float3(0.0f, 0.0f, 0.0f));
	carBodyTransform->SetLocalRotation(float3(0.0f, 0.0f, 0.0f));
	carBodyTransform->SetLocalScale(float3(1.0f, 0.2f, 2.0f));
	carBody->SetMesh(ArcApplication::m_assets->findMesh("Generated Box Mesh"));
	carBody->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	MainScene()->AddGameObject(carBody);

	auto carHead = std::make_shared<DX11Engine::ArcGameObject>("CarHead");
	DX11Engine::ArcGameObject::RegisterGameObject(carHead);
	auto carHeadTransform = std::make_shared<DX11Engine::ArcTransform>();
	carHead->SetTransfrom(carHeadTransform);
	DX11Engine::ArcTransform::SetParent(carHeadTransform, carTransform);
	carHeadTransform->SetLocalPosition(float3(0.0f, 0.2f, 0.0f));
	carHeadTransform->SetLocalRotation(float3(0.0f, 0.0f, 0.0f));
	carHeadTransform->SetLocalScale(float3(1.0f, 0.2f, 0.8f));
	carHead->SetMesh(ArcApplication::m_assets->findMesh("Generated Box Mesh"));
	carHead->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	MainScene()->AddGameObject(carHead);

	auto leftForwardWheel = std::make_shared<DX11Engine::ArcGameObject>("LeftBackwardWheel");
	DX11Engine::ArcGameObject::RegisterGameObject(leftForwardWheel);
	auto leftForwardWheelTransform = std::make_shared<DX11Engine::ArcTransform>();
	leftForwardWheel->SetTransfrom(leftForwardWheelTransform);
	DX11Engine::ArcTransform::SetParent(leftForwardWheelTransform, carTransform);
	leftForwardWheelTransform->SetLocalPosition(float3(-0.5f, 0.f, -0.6f));
	leftForwardWheelTransform->SetLocalRotation(float3(90.0f, 0.0f, 90.0f));
	leftForwardWheelTransform->SetScale(float3(0.4f, 0.05f, 0.4f));
	leftForwardWheel->SetMesh(ArcApplication::m_assets->findMesh("Cylinder Mesh"));
	leftForwardWheel->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	auto wheelMoveLB = std::make_shared<WheelMove>();
	leftForwardWheel->AttachScript(wheelMoveLB);
	MainScene()->AddGameObject(leftForwardWheel);

	auto rightBackwardWheel = std::make_shared<DX11Engine::ArcGameObject>("LeftForwardWheel");
	DX11Engine::ArcGameObject::RegisterGameObject(rightBackwardWheel);
	auto rightBackwardWheelTransform = std::make_shared<DX11Engine::ArcTransform>();
	rightBackwardWheel->SetTransfrom(rightBackwardWheelTransform);
	DX11Engine::ArcTransform::SetParent(rightBackwardWheelTransform, carTransform);
	rightBackwardWheelTransform->SetLocalPosition(float3(-0.5f, 0.f, 0.6f));
	rightBackwardWheelTransform->SetLocalRotation(float3(90.0f, 0.0f, 90.0f));
	rightBackwardWheelTransform->SetScale(float3(0.4f, 0.05f, 0.4f));
	rightBackwardWheel->SetMesh(ArcApplication::m_assets->findMesh("Cylinder Mesh"));
	rightBackwardWheel->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	auto wheelMoveLF = std::make_shared<WheelMove>();
	wheelMoveLF->isForwardWheel = true;
	rightBackwardWheel->AttachScript(wheelMoveLF);
	MainScene()->AddGameObject(rightBackwardWheel);

	auto rightForwardWheel = std::make_shared<DX11Engine::ArcGameObject>("RightForwardWheel");
	DX11Engine::ArcGameObject::RegisterGameObject(rightForwardWheel);
	auto rightForwardWheelTransform = std::make_shared<DX11Engine::ArcTransform>();
	rightForwardWheel->SetTransfrom(rightForwardWheelTransform);
	DX11Engine::ArcTransform::SetParent(rightForwardWheelTransform, carTransform);
	rightForwardWheelTransform->SetLocalPosition(float3(0.5f, 0.f, 0.6f));
	rightForwardWheelTransform->SetLocalRotation(float3(90.0f, 0.0f, 90.0f));
	rightForwardWheelTransform->SetScale(float3(0.4f, 0.05f, 0.4f));
	rightForwardWheel->SetMesh(ArcApplication::m_assets->findMesh("Cylinder Mesh"));
	rightForwardWheel->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	auto wheelMoveRF = std::make_shared<WheelMove>();
	wheelMoveRF->isForwardWheel = true;
	rightForwardWheel->AttachScript(wheelMoveRF);
	MainScene()->AddGameObject(rightForwardWheel);

	auto leftBackwardWheel = std::make_shared<DX11Engine::ArcGameObject>("RightBackwardWheel");
	DX11Engine::ArcGameObject::RegisterGameObject(leftBackwardWheel);
	auto leftBackwardWheelTransform = std::make_shared<DX11Engine::ArcTransform>();
	leftBackwardWheel->SetTransfrom(leftBackwardWheelTransform);
	DX11Engine::ArcTransform::SetParent(leftBackwardWheelTransform, carTransform);
	leftBackwardWheelTransform->SetLocalPosition(float3(0.5f, 0.f, -0.6f));
	leftBackwardWheelTransform->SetLocalRotation(float3(90.0f, 0.0f, 90.0f));
	leftBackwardWheelTransform->SetScale(float3(0.4f, 0.05f, 0.4f));
	leftBackwardWheel->SetMesh(ArcApplication::m_assets->findMesh("Cylinder Mesh"));
	leftBackwardWheel->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	auto wheelMoveRB = std::make_shared<WheelMove>();
	leftBackwardWheel->AttachScript(wheelMoveRB);
	MainScene()->AddGameObject(leftBackwardWheel);

	auto cameraPivotFirstPerson = std::make_shared<DX11Engine::ArcGameObject>("CameraPivotFirstPerson");
	DX11Engine::ArcGameObject::RegisterGameObject(cameraPivotFirstPerson);
	auto cameraPivotFirstPersonTransform = std::make_shared<DX11Engine::ArcTransform>();
	cameraPivotFirstPerson->SetTransfrom(cameraPivotFirstPersonTransform);
	DX11Engine::ArcTransform::SetParent(cameraPivotFirstPersonTransform, carTransform);
	cameraPivotFirstPersonTransform->SetLocalPosition(float3(0.f, 0.54f, 0.f));
	cameraPivotFirstPersonTransform->SetLocalRotation(float3(0.0f, 0.0f, 0.0f));
	cameraPivotFirstPersonTransform->SetScale(float3(1.f, 1.f, 1.f));
	MainScene()->AddGameObject(cameraPivotFirstPerson);

	auto cameraPivotThirdPerson = std::make_shared<DX11Engine::ArcGameObject>("CameraPivotThirdPerson");
	DX11Engine::ArcGameObject::RegisterGameObject(cameraPivotThirdPerson);
	auto cameraPivotThirdPersonTransform = std::make_shared<DX11Engine::ArcTransform>();
	cameraPivotThirdPerson->SetTransfrom(cameraPivotThirdPersonTransform);
	DX11Engine::ArcTransform::SetParent(cameraPivotThirdPersonTransform, carTransform);
	cameraPivotThirdPersonTransform->SetLocalPosition(float3(0.f, 1.48f, -2.5f));
	cameraPivotThirdPersonTransform->SetLocalRotation(float3(0.0f, 0.0f, 0.0f));
	cameraPivotThirdPersonTransform->SetScale(float3(1.f, 1.f, 1.f));
	MainScene()->AddGameObject(cameraPivotThirdPerson);
	
	auto cat = std::make_shared<DX11Engine::ArcGameObject>("Cat");
	DX11Engine::ArcGameObject::RegisterGameObject(cat);
	auto catTransform = std::make_shared<DX11Engine::ArcTransform>();
	catTransform->SetLocalPosition(float3(6.0f, 0.2f, 6.0f));
	catTransform->SetLocalRotation(float3(0.0f, 270.0f, 0.0f));
	//catTransform->SetLocalScale(float3(0.005f, 0.005f, 0.005f));
	cat->SetTransfrom(catTransform);
	cat->SetMesh(ArcApplication::m_assets->findMesh("Cornell Box"));
	cat->SetMaterial(ArcApplication::m_assets->findMaterial("StandardMaterial"));
	MainScene()->AddGameObject(cat);/**/
}