#pragma once

#include "CommonHeaders.h"
#include "ArcBehaviour.h"
#include "ArcMath.h"
#include "ArcInput.h"
#include "ArcTime.h"

class CameraMove :
	public DX11Engine::ArcBehaviour
{
public:
	void Awake();
	void Start();
	void Update();
private:
	float moveSpeed = 1.f;
};

