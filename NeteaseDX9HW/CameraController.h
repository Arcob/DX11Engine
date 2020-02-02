#pragma once
#include "ArcBehaviour.h"
#include "ArcTransform.h"

class CameraController :
	public DX11Engine::ArcBehaviour
{
	enum FollowType
	{
		None = 0,
		FirstPerson = 1,
		ThirdPerson = 2,
		Max = 3
	};
public:
	void Awake();
	void Start();
	void Update();

private:
	FollowType followType = FirstPerson;
	FollowType lastFrameType = FirstPerson;

	std::shared_ptr<DX11Engine::ArcTransform> firstPersonPivot;
	std::shared_ptr<DX11Engine::ArcTransform> thirdPersonPivot;
	std::shared_ptr<DX11Engine::ArcTransform> carTransform;

	float rotateSpeed = 50.f;
	float thirdCameraMoveSpeed = 30.0f;
	float maxThirdCameraDistanceMult = 2.0f;
	float minThirdCameraDistanceMult = 0.3f;
	float maxThirdCameraDistance = 100.f;
	float minThirdCameraDistance = 1.0f;
	float maxLookupAngel = 60.f;
};

