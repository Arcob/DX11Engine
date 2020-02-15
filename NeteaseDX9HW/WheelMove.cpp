#include "WheelMove.h"
#include "ArcGameObject.h"

void WheelMove::Awake() {
	//print("Awake");
}

void WheelMove::Start() {
	//print("Start");
	carTransform = GameObject()->Find("Car")->TransformPtr();
	circumference = 2.f * PI * wheelRadius;
}

void WheelMove::Update() {
	//print("Update");
	if (DX11Engine::ArcInput::GetKeyboardKey('W')) {
		GameObject()->TransformPtr()->RotateAround(GameObject()->TransformPtr()->Position(), float3(1.0f, 0.f, 0.f), moveSpeed / circumference * 360.f * DX11Engine::ArcTime::DeltaTime());
	}
	if (DX11Engine::ArcInput::GetKeyboardKey('S')) {
		GameObject()->TransformPtr()->RotateAround(GameObject()->TransformPtr()->Position(), float3(1.0f, 0.f, 0.f), -0.5f * moveSpeed / circumference * 360.f * DX11Engine::ArcTime::DeltaTime());
	}
	if (isForwardWheel)
	{
		if (DX11Engine::ArcInput::GetKeyboardKey('A'))
		{
			if (rotateSum > -forwardWheelMaxRotate)
			{
				GameObject()->TransformPtr()->RotateAround(GameObject()->TransformPtr()->Position(), carTransform->Up(), -rotateSpeed * DX11Engine::ArcTime::DeltaTime());
				rotateSum += -rotateSpeed * DX11Engine::ArcTime::DeltaTime();
			}
		}
		else if (DX11Engine::ArcInput::GetKeyboardKey('D'))
		{
			if (rotateSum < forwardWheelMaxRotate)
			{
				GameObject()->TransformPtr()->RotateAround(GameObject()->TransformPtr()->Position(), carTransform->Up(), rotateSpeed * DX11Engine::ArcTime::DeltaTime());
				rotateSum += rotateSpeed * DX11Engine::ArcTime::DeltaTime();
			}
		}
		else
		{
			if (rotateSum > 1.0f)
			{
				GameObject()->TransformPtr()->RotateAround(GameObject()->TransformPtr()->Position(), carTransform->Up(), -rotateSpeed * DX11Engine::ArcTime::DeltaTime());
				rotateSum += -rotateSpeed * DX11Engine::ArcTime::DeltaTime();
			}
			else if (rotateSum < -1.0f)
			{
				GameObject()->TransformPtr()->RotateAround(GameObject()->TransformPtr()->Position(), carTransform->Up(), rotateSpeed * DX11Engine::ArcTime::DeltaTime());
				rotateSum += rotateSpeed * DX11Engine::ArcTime::DeltaTime();
			}
		}
	}
}