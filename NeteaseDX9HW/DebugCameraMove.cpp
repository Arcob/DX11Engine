#include "DebugCameraMove.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcMath.h"

void DebugCameraMove::Awake() {
	//print("Awake");
}

void DebugCameraMove::Start() {
	auto camera = DX11Engine::ArcGameObject::Find("Camera");
	//camera->TransformPtr()->RotateAround(DX11Engine::ArcGameObject::Find("TestBoxWithNormal")->TransformPtr()->Position(), Float3Up(), 45.0f);

	//print("Start");
}

void DebugCameraMove::Update() {
	//print("Update");
	auto camera = DX11Engine::ArcGameObject::Find("Camera");
	if (DX11Engine::ArcInput::GetKeyboardKey('W')) {		
		camera->TransformPtr()->Translate(MultFloat3(camera->TransformPtr()->Forward(),  moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	else if (DX11Engine::ArcInput::GetKeyboardKey('A')) {
		camera->TransformPtr()->Translate(MultFloat3(camera->TransformPtr()->Right(), -moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	else if (DX11Engine::ArcInput::GetKeyboardKey('S')) {
		camera->TransformPtr()->Translate(MultFloat3(camera->TransformPtr()->Forward(), -moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	else if (DX11Engine::ArcInput::GetKeyboardKey('D')) {
		camera->TransformPtr()->Translate(MultFloat3(camera->TransformPtr()->Right(), moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	/**/if (DX11Engine::ArcInput::GetMouseKey(DX11Engine::MouseKey::LeftClick)) {
		float2 mousePosOrigin = DX11Engine::ArcInput::GetMousePos();
		float2 mousePos = float2(mousePosOrigin.x-0.5f, mousePosOrigin.y-0.5f);
		camera->TransformPtr()->Rotate(float3(rotateSpeed * mousePos.y * DX11Engine::ArcTime::DeltaTime(), rotateSpeed * mousePos.x * DX11Engine::ArcTime::DeltaTime(), 0.f));
	}
	//camera->TransformPtr()->RotateAround(DX11Engine::ArcGameObject::Find("TestBoxWithNormal")->TransformPtr()->Position(), Float3Up(), 10.0f * DX11Engine::ArcTime::DeltaTime());
	//PrintFloat3(camera->TransformPtr()->Position());
}