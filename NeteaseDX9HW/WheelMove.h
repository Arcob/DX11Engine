#pragma once
#include "ArcBehaviour.h"
#include "ArcTransform.h"
#include "ArcMath.h"
#include "ArcInput.h"
#include "ArcTime.h"

class WheelMove :
	public DX11Engine::ArcBehaviour
{
public:
	bool isForwardWheel = false;

	void Awake();
	void Start();
	void Update();
private:
	float moveSpeed = 5.0f;
	float rotateSpeed = 60.f;
	float wheelRadius = 0.4f;
	float circumference = 1.f;
	float forwardWheelMaxRotate = 20.f;
	float rotateSum = 0;
	std::shared_ptr<DX11Engine::ArcTransform> carTransform;
};

