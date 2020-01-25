#pragma once
#include "CommonHeaders.h"
#include "ArcStructures.h"
#include "ArcMath.h"

class ArcGeometryGenerator
{
public:
	struct MeshData
	{
		std::vector<DX11Engine::VertexNormalTangentTex>	vertices;
		std::vector<UINT> indices;
	};

	static void CreateSphere(float radius, int slice, int stack, MeshData &mesh);
};

