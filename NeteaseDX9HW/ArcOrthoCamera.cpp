#include "ArcOrthoCamera.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"

namespace DX11Engine{

	ArcOrthoCamera::ArcOrthoCamera() : ArcCameraBase(){
		cameraType = Orthographic;
		SetOrthoPara(50.f, 50.f, 0.3f, 100.0f);
	}

	ArcOrthoCamera::ArcOrthoCamera(float width, float height, float nearZ, float farZ) : ArcCameraBase() {
		cameraType = Orthographic;
		SetOrthoPara(width, height, nearZ, farZ);
	}

	void ArcOrthoCamera::SetOrthoPara(float width, float height, float nearZ, float farZ) {
		m_width = width;
		m_height = height;
		m_nearPlane = nearZ;
		m_farPlane = farZ;
	}
	
	mat4 const ArcOrthoCamera::Matrix() {
		return Projection() * View();
	}

	mat4 const ArcOrthoCamera::Projection() { //正交相机用正交投影矩阵
		return CalculateOrthographicMatrix(m_width, m_height, m_nearPlane, m_farPlane);
	}

	mat4 const ArcOrthoCamera::View() {
		float3 up = GameObject()->TransformPtr()->Up();
		float3 forward = GameObject()->TransformPtr()->Forward();
		float3 lookatPos = AddFloat3(forward, GameObject()->TransformPtr()->Position());
		return CalculateViewMatrix(GameObject()->TransformPtr()->Position(), lookatPos, up);
	}
}