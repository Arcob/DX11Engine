#include "CameraMove.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "ArcMath.h"

void CameraMove::Awake() {
	//print("Awake");
}

void CameraMove::Start() {
	//print("Start");
}

void CameraMove::Update() {
	//print("Update");
	if (DX11Engine::ArcInput::getKey('W')) {
		auto camera = DX11Engine::ArcGameObject::Find("Camera");
		camera->TransformPtr()->Translate(float3(0.f, 0.f, 1.f * moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	else if (DX11Engine::ArcInput::getKey('A')) {
		auto camera = DX11Engine::ArcGameObject::Find("Camera");
		camera->TransformPtr()->Translate(float3(-1.f * moveSpeed * DX11Engine::ArcTime::DeltaTime(), 0.f, 0.f));
	}
	else if (DX11Engine::ArcInput::getKey('S')) {
		auto camera = DX11Engine::ArcGameObject::Find("Camera");
		camera->TransformPtr()->Translate(float3(0.f, 0.f, -1.0f * moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	else if (DX11Engine::ArcInput::getKey('D')) {
		auto camera = DX11Engine::ArcGameObject::Find("Camera");
		camera->TransformPtr()->Translate(float3(1.0f * moveSpeed * DX11Engine::ArcTime::DeltaTime(), 0.f, 0.f));
	}
}