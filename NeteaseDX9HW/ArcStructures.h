#pragma once

#include "CommonHeaders.h"
#include "ArcMath.h"

namespace DX11Engine {
	struct Vertex
	{
		float3 pos;
		float4 color;
	};

	struct VertexNormalTangentTex
	{
	public:
		float3 pos;
		float3 normal;
		float3 tangent;
		float2 texCoord;

		VertexNormalTangentTex() = default;

		VertexNormalTangentTex(float3 _pos, float3 _normal, float3 _tangent, float2 _texCoord) {
			pos = _pos;
			normal = _normal;
			tangent = _tangent;
			texCoord = _texCoord;
		}
	};

	struct ConstantBufferMvp
	{
		mat4 mWorld;
		mat4 mView;
		mat4 mProjection;
	};

	struct ConstantBufferLight 
	{
		float3 Direction;
		float Intensity;
		float4 Color;
		float3 Position;
		float Pad1;
	};

	struct VertexPosNormalTex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 tex;
	};
}

