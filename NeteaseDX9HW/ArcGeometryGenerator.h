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
	static void CreateBox(float width, float height, float depth, MeshData &mesh);
	static void CreateCylinder(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	//给现成的圆柱添加上口
	static void AddCylinderTopCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	//给现成的圆柱添加下口
	static void AddCylinderBottomCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
};

