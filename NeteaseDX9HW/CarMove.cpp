#include "CarMove.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"

void CarMove::Awake() {
	//print("Awake");
}

void CarMove::Start() {
	//print("Start");
}

void CarMove::Update() {
	//print("Update");
	if (DX11Engine::ArcInput::GetKeyboardKey('W')) {
		GameObject()->TransformPtr()->Translate(MultFloat3(GameObject()->TransformPtr()->Forward(), moveSpeed * DX11Engine::ArcTime::DeltaTime()));
	}
	if (DX11Engine::ArcInput::GetKeyboardKey('S')) {
		GameObject()->TransformPtr()->Translate(MultFloat3(GameObject()->TransformPtr()->Forward(), -moveSpeed * 0.5f * DX11Engine::ArcTime::DeltaTime()));
	}
	if (DX11Engine::ArcInput::GetKeyboardKey('A')) {
		if (DX11Engine::ArcInput::GetKeyboardKey('W')) {
			GameObject()->TransformPtr()->Rotate(MultFloat3(GameObject()->TransformPtr()->Up(), -rotateSpeed * DX11Engine::ArcTime::DeltaTime()));
		}
		else if (DX11Engine::ArcInput::GetKeyboardKey('S')) 
		{
			GameObject()->TransformPtr()->Rotate(MultFloat3(GameObject()->TransformPtr()->Up(), rotateSpeed * DX11Engine::ArcTime::DeltaTime()));
		}
	}
	if (DX11Engine::ArcInput::GetKeyboardKey('D')) {
		if (DX11Engine::ArcInput::GetKeyboardKey('W')) {
			GameObject()->TransformPtr()->Rotate(MultFloat3(GameObject()->TransformPtr()->Up(), rotateSpeed * DX11Engine::ArcTime::DeltaTime()));
		}
		else if (DX11Engine::ArcInput::GetKeyboardKey('S')) 
		{
			GameObject()->TransformPtr()->Rotate(MultFloat3(GameObject()->TransformPtr()->Up(), -rotateSpeed * DX11Engine::ArcTime::DeltaTime()));
		}
	}
}