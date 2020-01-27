#include "SkyboxFollowCamera.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"

void SkyboxFollowCamera::Awake() {
	//print("Awake");
}

void SkyboxFollowCamera::Start() {
	//print("Start");
}

void SkyboxFollowCamera::Update() {
	//print("Update");
	auto camera = DX11Engine::ArcGameObject::Find("Camera");
	GameObject()->TransformPtr()->SetLocalPosition(camera->TransformPtr()->LocalPosition());
}