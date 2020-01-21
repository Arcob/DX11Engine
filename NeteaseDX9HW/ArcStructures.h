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
		float3 pos;
		float3 normal;
		float3 tangent;
		float2 texCoord;
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
	};

	struct VertexPosNormalTex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 tex;
	};
}

