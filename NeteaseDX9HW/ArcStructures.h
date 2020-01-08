#pragma once

#include "CommonHeaders.h"
#include "ArcMath.h"

namespace DX11Engine {
	struct Vertex
	{
		float3 pos;
		float4 color;
	};

	struct ConstantBuffer
	{
		mat4 mWorld;
		mat4 mView;
		mat4 mProjection;
	};
}

