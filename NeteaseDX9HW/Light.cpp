#include "Light.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"

namespace DX11Engine {
	DirectionalLight::DirectionalLight(float3 direction, float intensity, float4 color, float3 position, float4 cam) {
		Light::m_Type = LightType::TypeDirectionalLight;
		m_direction = direction;
		m_intensity = intensity;
		m_position = position;
		m_color = color;
		m_orthoCamPara = cam;
	}

	DirectionalLight::DirectionalLight(float intensity, float4 color, float4 cam) {
		Light::m_Type = LightType::TypeDirectionalLight;
		m_intensity = intensity;
		m_color = color;
		m_orthoCamPara = cam;
	}

	mat4 DirectionalLight::View() {
		float3 up = GameObject()->TransformPtr()->Up();
		float3 forward = GameObject()->TransformPtr()->Forward();
		float3 lookatPos = AddFloat3(forward, GameObject()->TransformPtr()->Position());
		return CalculateViewMatrix(GameObject()->TransformPtr()->Position(), lookatPos, up);
	}

	mat4 DirectionalLight::Orthographic() {
		return CalculateOrthographicMatrix(m_orthoCamPara.x, m_orthoCamPara.y, m_orthoCamPara.z, m_orthoCamPara.w);
	}
}