#pragma once
#include "ArcBehaviour.h"
#include "ArcMath.h"

class ArcCameraBase :
	public DX11Engine::ArcBehaviour
{
	enum CameraType
	{
		Perspective = 0,
		Orthographic = 1
	};

public:
	virtual mat4 Matrix() = 0;
	virtual mat4 Projection() = 0;
	virtual mat4 View() = 0;

private:
	float m_nearPlane;
	float m_farPlane;
};

