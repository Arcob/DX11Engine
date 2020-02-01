#pragma once
#include "ArcBehaviour.h"
#include "ArcBehaviour.h"
#include "ArcMath.h"
#include "ArcInput.h"
#include "ArcTime.h"

class CarMove :
	public DX11Engine::ArcBehaviour
{
public:
	void Awake();
	void Start();
	void Update();
private:
	float moveSpeed = 5.0f;
	float rotateSpeed = 30.f;
};

