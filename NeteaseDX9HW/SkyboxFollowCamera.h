#pragma once
#include "ArcBehaviour.h"
class SkyboxFollowCamera :
	public DX11Engine::ArcBehaviour
{
public:
	void Awake();
	void Start();
	void Update();
};

