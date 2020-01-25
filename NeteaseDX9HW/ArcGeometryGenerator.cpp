#include "ArcGeometryGenerator.h"

void ArcGeometryGenerator::CreateSphere(float radius, int slice, int stack, MeshData &mesh)
{

	mesh.vertices.clear();
	mesh.indices.clear();

	int vertsPerRow = slice + 1;
	int nRows = stack - 1;

	int nVerts = vertsPerRow * nRows + 2;
	int nIndices = (nRows - 1)*slice * 6 + slice * 6;

	mesh.vertices.resize(nVerts);
	mesh.indices.resize(nIndices);

	for (int i = 1; i <= nRows; ++i)
	{
		float phy = PI * i / stack;
		float tmpRadius = radius * sin(phy);
		for (int j = 0; j < vertsPerRow; ++j)
		{
			float theta = PI * 2.f * j / slice;
			UINT index = (i - 1)*vertsPerRow + j;

			float x = tmpRadius * cos(theta);
			float y = radius * cos(phy);
			float z = tmpRadius * sin(theta);

			//位置坐标
			mesh.vertices[index].pos = float3(x, y, z);
			//法线
			DirectX::XMVECTOR N = DirectX::XMVectorSet(x, y, z, 0.f);
			XMStoreFloat3(&mesh.vertices[index].normal, DirectX::XMVector3Normalize(N));
			//切线
			DirectX::XMVECTOR T = DirectX::XMVectorSet(-sin(theta), 0.f, cos(theta), 0.f);
			XMStoreFloat3(&mesh.vertices[index].tangent, DirectX::XMVector3Normalize(T));
			//纹理坐标
			mesh.vertices[index].texCoord = float2(j*1.f / slice, i*1.f / stack);
		}
	}

	int size = vertsPerRow * nRows;
	//添加顶部和底部两个顶点信息
	mesh.vertices[size].pos = float3(0.f, radius, 0.f);
	mesh.vertices[size].normal = float3(0.f, 1.f, 0.f);
	mesh.vertices[size].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[size].texCoord = float2(0.f, 0.f);

	mesh.vertices[size + 1].pos = float3(0.f, -radius, 0.f);
	mesh.vertices[size + 1].normal = float3(0.f, -1.f, 0.f);
	mesh.vertices[size + 1].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[size + 1].texCoord = float2(0.f, 1.f);

	UINT tmp(0);
	int start1 = 0;
	int start2 = mesh.vertices.size() - vertsPerRow - 2;
	int top = size;
	int bottom = size + 1;
	for (int i = 0; i < slice; ++i)
	{
		mesh.indices[tmp] = top;
		mesh.indices[tmp + 1] = start1 + i + 1;
		mesh.indices[tmp + 2] = start1 + i;

		tmp += 3;
	}

	for (int i = 0; i < slice; ++i)
	{
		mesh.indices[tmp] = bottom;
		mesh.indices[tmp + 1] = start2 + i;
		mesh.indices[tmp + 2] = start2 + i + 1;

		tmp += 3;
	}

	for (int i = 0; i < nRows - 1; ++i)
	{
		for (int j = 0; j < slice; ++j)
		{
			mesh.indices[tmp] = i * vertsPerRow + j;
			mesh.indices[tmp + 1] = (i + 1) * vertsPerRow + j + 1;
			mesh.indices[tmp + 2] = (i + 1) * vertsPerRow + j;
			mesh.indices[tmp + 3] = i * vertsPerRow + j;
			mesh.indices[tmp + 4] = i * vertsPerRow + j + 1;
			mesh.indices[tmp + 5] = (i + 1) * vertsPerRow + j + 1;

			tmp += 6;
		}
	}
}