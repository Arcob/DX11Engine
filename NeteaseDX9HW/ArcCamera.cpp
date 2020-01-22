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
		return CalculatePerspectiveMatrix(DegreeToRadians(m_fieldOfView), m_viewportAspectRatio, m_nearPlane, m_farPlane);
	}

	mat4 ArcCamera::View() const {
		mat4 temp = GameObject()->TransformPtr()->PositionMatrix() * GameObject()->TransformPtr()->RotationMatrix();
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(temp);
		temp = DirectX::XMMatrixInverse(&det, temp);
		return temp;
	}

}