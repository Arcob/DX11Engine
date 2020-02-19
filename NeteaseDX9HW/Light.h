#pragma once
#include "ArcMath.h"
#include "ArcBehaviour.h"

namespace DX11Engine {
	enum LightType {
		TypeNone = 0,
		TypeDirectionalLight = 1,
		TypeSpotLight = 2,
		TypePointLight = 3,
		TypeAreaLight = 4,
		TypeMax = 5
	};

	class Light :
		public ArcBehaviour
	{
	public:
		LightType m_Type;
	};

	class DirectionalLight : public Light {
	public:
		float3 m_direction;
		float m_intensity;
		float4 m_color;
		float3 m_position;
		float4 m_orthoCamPara; // ViewWidth, ViewHeight, NearZ, FarZ

		DirectionalLight(float3 direction, float intensity, float4 color, float3 position, float4 cam);
		DirectionalLight(float intensity, float4 color, float4 cam);
		mat4 View();
		mat4 Orthographic();
	};

}