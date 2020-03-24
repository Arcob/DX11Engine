#include "ArcCamera.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"
#include "DriverSetting.h"

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
		assert(fieldOfView > 0.0f && fieldOfView < 180.0f);//assertЧ������������������ش�������ֹ����ִ��
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
		return GetFrustumCorners(m_nearPlane,m_farPlane);
	}

	std::shared_ptr<ArcCamera::FrustumCorners> ArcCamera::GetFrustumCorners(float nearPlane, float farPlane) {
		std::shared_ptr<ArcCamera::FrustumCorners> result = std::make_shared<ArcCamera::FrustumCorners>();
		auto cameraTrans = GameObject()->getComponent<ArcTransform>();
		ArcCamera::FrustumCorners viewSpaceCorners;
		mat4 tempPro = CalculatePerspectiveMatrix(DegreeToRadians(m_fieldOfView), m_viewportAspectRatio, nearPlane, farPlane);
		mat4 mat = Inverse(View() * tempPro);
		float3 vecFrustum[8];
		vecFrustum[0] = float3(-1.0f, -1.0f, 0.0f); // xyz
		vecFrustum[1] = float3(1.0f, -1.0f, 0.0f); // Xyz
		vecFrustum[2] = float3(-1.0f, 1.0f, 0.0f); // xYz
		vecFrustum[3] = float3(1.0f, 1.0f, 0.0f); // XYz
		vecFrustum[4] = float3(-1.0f, -1.0f, 1.0f); // xyZ
		vecFrustum[5] = float3(1.0f, -1.0f, 1.0f); // XyZ
		vecFrustum[6] = float3(-1.0f, 1.0f, 1.0f); // xYZ
		vecFrustum[7] = float3(1.0f, 1.0f, 1.0f); // XYZ

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

		return result;
	}

	void ArcCamera::GetCascadeFrustumCornersList(std::vector<std::shared_ptr<ArcCamera::FrustumCorners>>& list) {
		list.clear();
		std::vector<float> tempPlaneDis = std::vector<float>(2 + SHADOW_CASCADE_LAYER_NUM - 1);
		tempPlaneDis[0] = m_nearPlane;
		tempPlaneDis[tempPlaneDis.size() - 1] = (m_farPlane < SHADOW_DISTANCE) ? m_farPlane : SHADOW_DISTANCE;
		for (int i = 1; i < tempPlaneDis.size() - 1; ++i) {
			tempPlaneDis[i] = SHADOW_DISTANCE * CACSCADE_SHADOW_MAP_BOUND_PERCENT[i-1];
		}
		for (int i = 0; i < SHADOW_CASCADE_LAYER_NUM; ++i) {
			list.push_back(GetFrustumCorners(tempPlaneDis[i], tempPlaneDis[i+1]));
			//print(tempPlaneDis[i] << " " << tempPlaneDis[i + 1]);
		}
	}
}