#pragma once

#include "CommonHeaders.h"
#include "ArcBehaviour.h"
#include "ArcCameraBase.h"
#include "ArcMath.h"

namespace DX11Engine{

class ArcPrespCamera : 
	public ArcCameraBase
{
public:
	ArcPrespCamera();

	struct FrustumCorners{
	public:
		float3 nearCorners[4];
		float3 farCorners[4];
	};

	//std::vector<std::shared_ptr<ArcCamera::FrustumCorners>> cascadeFrustumsCornerVector;
	
	float FieldOfView() const;
	void SetFieldOfView(float fieldOfView);

	float NearPlane() const;
	float FarPlane() const;
	void SetNearAndFarPlanes(float nearPlane, float farPlane);

	float ViewportAspectRatio() const;
	void SetViewportAspectRatio(float viewportAspectRatio);
	std::shared_ptr<ArcPrespCamera::FrustumCorners> GetFrustumCorners();
	void GetCascadeFrustumCornersList(std::vector<std::shared_ptr<ArcPrespCamera::FrustumCorners>>& list);

	mat4 const Matrix();
	mat4 const Projection();
	mat4 const View();

private:
	float m_fieldOfView;
	float m_nearPlane;
	float m_farPlane;
	float m_viewportAspectRatio;

	std::shared_ptr<ArcPrespCamera::FrustumCorners> GetFrustumCorners(float nearPlane, float farPlane);
};

}
