#include "ArcCamera.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"

namespace DX11Engine {

	static const float MaxVerticalAngle = 85.0f;

	ArcCamera::ArcCamera() :
		m_fieldOfView(60.0f),
		m_nearPlane(0.3f),
		m_farPlane(100.0f),
		m_viewportAspectRatio(4.0f / 3.0f)
	{
	}

	float ArcCamera::FieldOfView() const {
		return m_fieldOfView;
	}

	void ArcCamera::SetFieldOfView(float fieldOfView) {
		assert(fieldOfView > 0.0f && fieldOfView < 180.0f);//assert效果是如果它的条件返回错误，则终止程序执行
		m_fieldOfView = fieldOfView;
	}

	float ArcCamera::NearPlane() const {
		return m_nearPlane;
	}

	float ArcCamera::FarPlane() const {
		return m_farPlane;
	}

	void ArcCamera::SetNearAndFarPlanes(float nearPlane, float farPlane) {
		assert(nearPlane > 0.0f);
		assert(farPlane > nearPlane);
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
	}

	float ArcCamera::ViewportAspectRatio() const {
		return m_viewportAspectRatio;
	}

	void ArcCamera::SetViewportAspectRatio(float viewportAspectRatio) {
		assert(viewportAspectRatio > 0.0);
		m_viewportAspectRatio = viewportAspectRatio;
	}

	mat4 ArcCamera::Matrix() const {
		return Projection() * View();
	}

	mat4 ArcCamera::Projection() const {
		//print(m_viewportAspectRatio);
		return CalculatePerspectiveMatrix(DegreeToRadians(m_fieldOfView), m_viewportAspectRatio, m_nearPlane, m_farPlane);
	}

	mat4 ArcCamera::View() const {
		float3 up = GameObject()->TransformPtr()->Up();
		float3 forward = GameObject()->TransformPtr()->Forward();
		float3 lookatPos = AddFloat3(forward, GameObject()->TransformPtr()->Position());
		return CalculateViewMatrix(GameObject()->TransformPtr()->Position(), lookatPos, up);
	}

	std::shared_ptr<ArcCamera::FrustumCorners> ArcCamera::GetFrustumCorners() {
		std::shared_ptr<ArcCamera::FrustumCorners> result = std::make_shared<ArcCamera::FrustumCorners>();
		auto cameraTrans = GameObject()->getComponent<ArcTransform>();
		ArcCamera::FrustumCorners viewSpaceCorners;
		mat4 mat = Inverse(View() * Projection());
		float3 vecFrustum[8];
		vecFrustum[0] = float3(-1.0f, -1.0f,  0.0f); // xyz
		vecFrustum[1] = float3( 1.0f, -1.0f,  0.0f); // Xyz
		vecFrustum[2] = float3(-1.0f,  1.0f,  0.0f); // xYz
		vecFrustum[3] = float3( 1.0f,  1.0f,  0.0f); // XYz
		vecFrustum[4] = float3(-1.0f, -1.0f,  1.0f); // xyZ
		vecFrustum[5] = float3( 1.0f, -1.0f,  1.0f); // XyZ
		vecFrustum[6] = float3(-1.0f,  1.0f,  1.0f); // xYZ
		vecFrustum[7] = float3( 1.0f,  1.0f,  1.0f); // XYZ

		for (int i = 0; i < 8; i++) {
			vecFrustum[i] = TransformCoord(vecFrustum[i], mat);
			//PrintFloat3(vecFrustum[i]);
		}
		result->nearCorners[0] = vecFrustum[0];
		result->nearCorners[1] = vecFrustum[1];
		result->nearCorners[2] = vecFrustum[2];
		result->nearCorners[3] = vecFrustum[3];

		result->farCorners[0] = vecFrustum[4];
		result->farCorners[1] = vecFrustum[5];
		result->farCorners[2] = vecFrustum[6];
		result->farCorners[3] = vecFrustum[7];
		//D3DXVec3TransformCoord(&vecFrustum, &vecFrustum, &mat);
		//D3DXMatrixMultiply(&mat, matView, matProj); 
		//D3DXMatrixInverse(&mat, NULL, &mat);
		return result;
	}
	//0. Variables:D3DXMATRIXA16 mat;D3DXVECTOR3 vecFrustum[8];
	//1. multiply the matrices together D3DXMatrixMultiply( &mat, matView, matProj );D3DXMatrixInverse( &mat, NULL, &mat );
	//2. create the 8 points of a cube in unit-space vecFrustum[0] = D3DXVECTOR3(-1.0f, -1.0f,  0.0f); 
	// xyzvecFrustum[1] = D3DXVECTOR3( 1.0f, -1.0f,  0.0f); 
	// XyzvecFrustum[2] = D3DXVECTOR3(-1.0f,  1.0f,  0.0f); 
	// xYzvecFrustum[3] = D3DXVECTOR3( 1.0f,  1.0f,  0.0f); 
	// XYzvecFrustum[4] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); 
	// xyZvecFrustum[5] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); 
	// XyZvecFrustum[6] = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); 
	// xYZvecFrustum[7] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); 
	// XYZ//3. transform all 8 points by the view/proj matrix. Doing this gives us that ACTUAL 8 corners of the frustum area.
	//for( int i = 0; i < 8; i++ )    D3DXVec3TransformCoord( &vecFrustum, &vecFrustum, &mat );
	//4. generate and store the 6 planes that make up the frustumD3DXPlaneFromPoints( &FrustumPlanes[0], &vecFrustum[0], 			&vecFrustum[1], &vecFrustum[2] ); // NearD3DXPlaneFromPoints( &FrustumPlanes[1], &vecFrustum[6], 			&vecFrustum[7], &vecFrustum[5] ); 
	// FarD3DXPlaneFromPoints( &FrustumPlanes[2], &vecFrustum[2], 			&vecFrustum[6], &vecFrustum[4] ); // LeftD3DXPlaneFromPoints( &FrustumPlanes[3], &vecFrustum[7], 			&vecFrustum[3], &vecFrustum[5] ); // RightD3DXPlaneFromPoints( &FrustumPlanes[4], &vecFrustum[2], 			&vecFrustum[3], &vecFrustum[6] ); // TopD3DXPlaneFromPoints( &FrustumPlanes[5], &vecFrustum[1], 			&vecFrustum[0], &vecFrustum[4] ); // Bottom
}