#pragma once

#include "CommonHeaders.h"
#include "ArcBehaviour.h"
#include "ArcMath.h"

namespace DX11Engine{

class ArcCamera : 
	public ArcBehaviour
{
public:
	ArcCamera();

	float FieldOfView() const;
	void SetFieldOfView(float fieldOfView);

	float NearPlane() const;
	float FarPlane() const;
	void SetNearAndFarPlanes(float nearPlane, float farPlane);

	float ViewportAspectRatio() const;
	void SetViewportAspectRatio(float viewportAspectRatio);

	mat4 Matrix() const;
	mat4 Projection() const;
	mat4 View() const;

private:
	float m_fieldOfView;
	float m_nearPlane;
	float m_farPlane;
	float m_viewportAspectRatio;
};

}
