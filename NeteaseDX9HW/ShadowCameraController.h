#pragma once
#include "ArcBehaviour.h"
#include "ArcPrespCamera.h"
#include "Light.h"

class ShadowCameraController :
	public DX11Engine::ArcBehaviour
{
public:
	void Awake();
	void Start();
	void Update();
private:
	DX11Engine::ArcPrespCamera* cachedMainCamera;
	DX11Engine::DirectionalLight* cachedDirectionalLight;
	void SetCurLightInfo();
	float cameraBackDistance = 500.f;
};

