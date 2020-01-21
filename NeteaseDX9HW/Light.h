#pragma once
#include "ArcMath.h"

namespace DX11Engine {
	enum LightType {
		TypeNone = 0,
		TypeDirectionalLight = 1,
		TypeSpotLight = 2,
		TypePointLight = 3,
		TypeAreaLight = 4,
		TypeMax = 5
	};

	class Light
	{
	public:
		LightType m_Type;
	};

	class DirectionalLight : public Light {
	public:
		float3 m_direction;
		float m_intensity;
		float4 m_color;
		DirectionalLight(float3 direction, float intensity, float4 color);
	};

}