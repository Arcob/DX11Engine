#include "DebugCameraMove.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcMath.h"

void DebugCameraMove::Awake() {
	//print("Awake");
}

void DebugCameraMove::Start() {
	//print("Start");
}

void DebugCameraMove::Update() {
	//print("Update");
	auto camera = DX11Engine::ArcGameObject::Find("Camera");
	if (DX11Engine::ArcInput::getKeyboardKey('W')) {		
		camera->TransformPtr()->Translate(float3(0.f, 0.f, 1.f * moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	else if (DX11Engine::ArcInput::getKeyboardKey('A')) {
		camera->TransformPtr()->Translate(float3(-1.f * moveSpeed * DX11Engine::ArcTime::DeltaTime(), 0.f, 0.f));
	}
	else if (DX11Engine::ArcInput::getKeyboardKey('S')) {
		camera->TransformPtr()->Translate(float3(0.f, 0.f, -1.0f * moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	else if (DX11Engine::ArcInput::getKeyboardKey('D')) {
		camera->TransformPtr()->Translate(float3(1.0f * moveSpeed * DX11Engine::ArcTime::DeltaTime(), 0.f, 0.f));
	}

	if (DX11Engine::ArcInput::getMouseKey(DX11Engine::MouseKey::LeftClick)) {
		float2 mousePosOrigin = DX11Engine::ArcInput::GetMousePos();
		float2 mousePos = float2(mousePosOrigin.x-0.5f, mousePosOrigin.y-0.5f);
		camera->TransformPtr()->Rotate(float3(rotateSpeed * mousePos.y * DX11Engine::ArcTime::DeltaTime(), rotateSpeed * mousePos.x * DX11Engine::ArcTime::DeltaTime(), 0.f));
	}
}