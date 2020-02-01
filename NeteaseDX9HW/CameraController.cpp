#include "CameraController.h"
#include "ArcGameObject.h"

void CameraController::Awake() {
	//print("Awake");
}

void CameraController::Start() {
	//print("Start");
	firstPersonPivot = DX11Engine::ArcGameObject::Find("CameraPivotFirstPerson")->TransformPtr();
	thirdPersonPivot = DX11Engine::ArcGameObject::Find("CameraPivotThirdPerson")->TransformPtr();
	carTransform = DX11Engine::ArcGameObject::Find("Car")->TransformPtr();
	GameObject()->TransformPtr()->SetPosition(firstPersonPivot->Position());
	GameObject()->TransformPtr()->SetRotation(firstPersonPivot->Rotation());
	maxThirdCameraDistance = DistanceFloat3(thirdPersonPivot->Position(), carTransform->Position()) * maxThirdCameraDistanceMult;
	minThirdCameraDistance = DistanceFloat3(thirdPersonPivot->Position(), carTransform->Position()) * minThirdCameraDistanceMult;
}

void CameraController::Update() {
	//print("Update");
	
}