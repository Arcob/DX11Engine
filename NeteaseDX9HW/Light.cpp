#include "Light.h"

namespace DX11Engine {
	DirectionalLight::DirectionalLight(float3 direction, float intensity, float4 color) {
		Light::m_Type = LightType::TypeDirectionalLight;
		m_direction = direction;
		m_intensity = intensity;
		m_color = color;
	}

}