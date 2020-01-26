#include "ArcGeometryGenerator.h"

void ArcGeometryGenerator::CreateBox(float width, float height, float depth, MeshData &mesh)
{
	mesh.vertices.clear();
	mesh.indices.clear();

	//一共24个顶点(每面4个)
	mesh.vertices.resize(24);
	//一共36个索引(每面6个)
	mesh.indices.resize(36);

	float halfW = width * 0.5f;
	float halfH = height * 0.5f;
	float halfD = depth * 0.5f;

	//眼睛面向z轴正方向
	//构建顶点
	//前面
	mesh.vertices[0].pos = float3(-halfW, -halfH, -halfD);
	mesh.vertices[0].normal = float3(0.f, 0.f, -1.f);
	mesh.vertices[0].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[0].texCoord = float2(0.f, 1.f);
	mesh.vertices[1].pos = float3(-halfW, halfH, -halfD);
	mesh.vertices[1].normal = float3(0.f, 0.f, -1.f);
	mesh.vertices[1].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[1].texCoord = float2(0.f, 0.f);
	mesh.vertices[2].pos = float3(halfW, halfH, -halfD);
	mesh.vertices[2].normal = float3(0.f, 0.f, -1.f);
	mesh.vertices[2].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[2].texCoord = float2(1.f, 0.f);
	mesh.vertices[3].pos = float3(halfW, -halfH, -halfD);
	mesh.vertices[3].normal = float3(0.f, 0.f, -1.f);
	mesh.vertices[3].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[3].texCoord = float2(1.f, 1.f);
	//左侧面
	mesh.vertices[4].pos = float3(-halfW, -halfH, halfD);
	mesh.vertices[4].normal = float3(-1.f, 0.f, 0.f);
	mesh.vertices[4].tangent = float3(0.f, 0.f, -1.f);
	mesh.vertices[4].texCoord = float2(0.f, 1.f);
	mesh.vertices[5].pos = float3(-halfW, halfH, halfD);
	mesh.vertices[5].normal = float3(-1.f, 0.f, 0.f);
	mesh.vertices[5].tangent = float3(0.f, 0.f, -1.f);
	mesh.vertices[5].texCoord = float2(0.f, 0.f);
	mesh.vertices[6].pos = float3(-halfW, halfH, -halfD);
	mesh.vertices[6].normal = float3(-1.f, 0.f, 0.f);
	mesh.vertices[6].tangent = float3(0.f, 0.f, -1.f);
	mesh.vertices[6].texCoord = float2(1.f, 0.f);
	mesh.vertices[7].pos = float3(-halfW, -halfH, -halfD);
	mesh.vertices[7].normal = float3(-1.f, 0.f, 0.f);
	mesh.vertices[7].tangent = float3(0.f, 0.f, -1.f);
	mesh.vertices[7].texCoord = float2(1.f, 1.f);
	//背面
	mesh.vertices[8].pos = float3(halfW, -halfH, halfD);
	mesh.vertices[8].normal = float3(0.f, 0.f, 1.f);
	mesh.vertices[8].tangent = float3(-1.f, 0.f, 0.f);
	mesh.vertices[8].texCoord = float2(0.f, 1.f);
	mesh.vertices[9].pos = float3(halfW, halfH, halfD);
	mesh.vertices[9].normal = float3(0.f, 0.f, 1.f);
	mesh.vertices[9].tangent = float3(-1.f, 0.f, 0.f);
	mesh.vertices[9].texCoord = float2(0.f, 0.f);
	mesh.vertices[10].pos = float3(-halfW, halfH, halfD);
	mesh.vertices[10].normal = float3(0.f, 0.f, 1.f);
	mesh.vertices[10].tangent = float3(-1.f, 0.f, 0.f);
	mesh.vertices[10].texCoord = float2(1.f, 0.f);
	mesh.vertices[11].pos = float3(-halfW, -halfH, halfD);
	mesh.vertices[11].normal = float3(0.f, 0.f, 1.f);
	mesh.vertices[11].tangent = float3(-1.f, 0.f, 0.f);
	mesh.vertices[11].texCoord = float2(1.f, 1.f);
	//右侧面
	mesh.vertices[12].pos = float3(halfW, -halfH, -halfD);
	mesh.vertices[12].normal = float3(1.f, 0.f, 0.f);
	mesh.vertices[12].tangent = float3(0.f, 0.f, 1.f);
	mesh.vertices[12].texCoord = float2(0.f, 1.f);
	mesh.vertices[13].pos = float3(halfW, halfH, -halfD);
	mesh.vertices[13].normal = float3(1.f, 0.f, 0.f);
	mesh.vertices[13].tangent = float3(0.f, 0.f, 1.f);
	mesh.vertices[13].texCoord = float2(0.f, 0.f);
	mesh.vertices[14].pos = float3(halfW, halfH, halfD);
	mesh.vertices[14].normal = float3(1.f, 0.f, 0.f);
	mesh.vertices[14].tangent = float3(0.f, 0.f, 1.f);
	mesh.vertices[14].texCoord = float2(1.f, 0.f);
	mesh.vertices[15].pos = float3(halfW, -halfH, halfD);
	mesh.vertices[15].normal = float3(1.f, 0.f, 0.f);
	mesh.vertices[15].tangent = float3(0.f, 0.f, 1.f);
	mesh.vertices[15].texCoord = float2(1.f, 1.f);
	//上面
	mesh.vertices[16].pos = float3(-halfW, halfH, -halfD);
	mesh.vertices[16].normal = float3(0.f, 1.f, 0.f);
	mesh.vertices[16].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[16].texCoord = float2(0.f, 1.f);
	mesh.vertices[17].pos = float3(-halfW, halfH, halfD);
	mesh.vertices[17].normal = float3(0.f, 1.f, 0.f);
	mesh.vertices[17].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[17].texCoord = float2(0.f, 0.f);
	mesh.vertices[18].pos = float3(halfW, halfH, halfD);
	mesh.vertices[18].normal = float3(0.f, 1.f, 0.f);
	mesh.vertices[18].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[18].texCoord = float2(1.f, 0.f);
	mesh.vertices[19].pos = float3(halfW, halfH, -halfD);
	mesh.vertices[19].normal = float3(0.f, 1.f, 0.f);
	mesh.vertices[19].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[19].texCoord = float2(1.f, 1.f);
	//底面
	mesh.vertices[20].pos = float3(-halfW, -halfH, halfD);
	mesh.vertices[20].normal = float3(0.f, -1.f, 0.f);
	mesh.vertices[20].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[20].texCoord = float2(0.f, 1.f);
	mesh.vertices[21].pos = float3(-halfW, -halfH, -halfD);
	mesh.vertices[21].normal = float3(0.f, -1.f, 0.f);
	mesh.vertices[21].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[21].texCoord = float2(0.f, 0.f);
	mesh.vertices[22].pos = float3(halfW, -halfH, -halfD);
	mesh.vertices[22].normal = float3(0.f, -1.f, 0.f);
	mesh.vertices[22].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[22].texCoord = float2(1.f, 0.f);
	mesh.vertices[23].pos = float3(halfW, -halfH, halfD);
	mesh.vertices[23].normal = float3(0.f, -1.f, 0.f);
	mesh.vertices[23].tangent = float3(1.f, 0.f, 0.f);
	mesh.vertices[23].texCoord = float2(1.f, 1.f);

	//构建索引
	mesh.indices[0] = 0;
	mesh.indices[1] = 1;
	mesh.indices[2] = 2;
	mesh.indices[3] = 0;
	mesh.indices[4] = 2;
	mesh.indices[5] = 3;

	mesh.indices[6] = 4;
	mesh.indices[7] = 5;
	mesh.indices[8] = 6;
	mesh.indices[9] = 4;
	mesh.indices[10] = 6;
	mesh.indices[11] = 7;

	mesh.indices[12] = 8;
	mesh.indices[13] = 9;
	mesh.indices[14] = 10;
	mesh.indices[15] = 8;
	mesh.indices[16] = 10;
	mesh.indices[17] = 11;

	mesh.indices[18] = 12;
	mesh.indices[19] = 13;
	mesh.indices[20] = 14;
	mesh.indices[21] = 12;
	mesh.indices[22] = 14;
	mesh.indices[23] = 15;

	mesh.indices[24] = 16;
	mesh.indices[25] = 17;
	mesh.indices[26] = 18;
	mesh.indices[27] = 16;
	mesh.indices[28] = 18;
	mesh.indices[29] = 19;

	mesh.indices[30] = 20;
	mesh.indices[31] = 21;
	mesh.indices[32] = 22;
	mesh.indices[33] = 20;
	mesh.indices[34] = 22;
	mesh.indices[35] = 23;
}

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

void ArcGeometryGenerator::CreateCylinder(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh)
{
	mesh.vertices.clear();
	mesh.indices.clear();

	//从上到下每个stack半径变化量:dRadius
	float dRadius = (bottomRadius - topRadius) / stack;
	//每个stack高度:dHeight
	float dHeight = height / stack;

	//每个圆周上顶点数量:slice+1
	int vertsPerRow = slice + 1;
	//顶点行数:stack+1
	int nRows = stack + 1;

	//总顶点数
	int nVerts = vertsPerRow * nRows;
	//总索引数
	int nIndices = slice * stack * 6;

	mesh.vertices.resize(nVerts);
	mesh.indices.resize(nIndices);

	//顶部Y坐标
	float topY = height * 0.5f;

	for (int i = 0; i < nRows; ++i)
	{
		float tmpY = topY - dHeight * i;
		float tmpRadius = topRadius + i * dRadius;

		for (int j = 0; j < vertsPerRow; ++j)
		{
			float theta = PI * 2 * j / slice;
			int index = i * vertsPerRow + j;
			mesh.vertices[index].pos = float3(tmpRadius*cos(theta), tmpY, tmpRadius*sin(theta));
		}
	}

	UINT tmp(0);
	for (int i = 0; i < stack; ++i)
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
