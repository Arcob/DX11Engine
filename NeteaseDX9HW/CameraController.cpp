#include "CameraController.h"
#include "ArcGameObject.h"
#include "ArcInput.h"
#include "ArcTime.h"

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
	std::shared_ptr<DX11Engine::ArcTransform> transform = GameObject()->TransformPtr();
	if (DX11Engine::ArcInput::getKeyboardKeyDown(' '))
	{
		if (followType == FirstPerson)
		{
			followType = ThirdPerson;
			transform->SetPosition(thirdPersonPivot->Position());
			transform->SetRotation(thirdPersonPivot->Rotation());
		}
		else if (followType == ThirdPerson)
		{
			followType = FirstPerson;
			transform->SetPosition(firstPersonPivot->Position());
			//transform->LookAt(carTransform->Position());
			transform->SetRotation(firstPersonPivot->Rotation());
		}
	
	}

	if (followType == FirstPerson)
	{
		transform->SetPosition(firstPersonPivot->Position());

		if (DX11Engine::ArcInput::GetMouseKey(DX11Engine::MouseKey::LeftClick))
		{
			transform->Rotate(MultFloat3(transform->Up(), rotateSpeed * DX11Engine::ArcTime::DeltaTime() * (DX11Engine::ArcInput::GetMousePos().x - 0.5f)));
		}
	}
	else if (followType == ThirdPerson) 
	{
		if (DX11Engine::ArcInput::GetMouseKey(DX11Engine::MouseKey::LeftClick))
		{
			thirdPersonPivot->RotateAround(carTransform->Position(), carTransform->Up(), rotateSpeed * DX11Engine::ArcTime::DeltaTime() * (DX11Engine::ArcInput::GetMousePos().x - 0.5f));
			float3 tempPos = thirdPersonPivot->Position();
			thirdPersonPivot->RotateAround(carTransform->Position(), GameObject()->TransformPtr()->Right(), rotateSpeed * DX11Engine::ArcTime::DeltaTime() * (DX11Engine::ArcInput::GetMousePos().y - 0.5f));
			if (AngleFloat3Degree(Float3Minus(thirdPersonPivot->Position(), carTransform->Position()), Float3Up()) < (90.0f - maxLookupAngel) || thirdPersonPivot->Position().y < carTransform->Position().y)
			{
				thirdPersonPivot->SetPosition(tempPos);
			}
		}

		if (DX11Engine::ArcInput::GetMouseScrollWheel() != 0)
		{
			float move = DX11Engine::ArcInput::GetMouseScrollWheel() * thirdCameraMoveSpeed * DX11Engine::ArcTime::DeltaTime();

			float3 lookAt = NormalizeFloat3(Float3Minus(thirdPersonPivot->Position(), carTransform->Position()));
			float3 minVec = AddFloat3(carTransform->Position(), MultFloat3(lookAt, minThirdCameraDistance));
			float3 maxVec = AddFloat3(carTransform->Position(), MultFloat3(lookAt, maxThirdCameraDistance));
			float lerpFactor = (DistanceFloat3(thirdPersonPivot->Position(), minVec) - move) / (maxThirdCameraDistance - minThirdCameraDistance);
			thirdPersonPivot->SetPosition(Float3Lerp(minVec, maxVec, lerpFactor));
		}
		transform->SetPosition(thirdPersonPivot->Position());
		transform->LookAt(carTransform->Position());
	}
}