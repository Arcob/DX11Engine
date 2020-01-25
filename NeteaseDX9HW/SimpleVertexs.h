#pragma once

#include "CommonHeaders.h"
#include "ArcMath.h"
#include "ArcStructures.h"

namespace DX11Engine {
	Vertex TestBoxVertices[8] =
	{
		{ float3(-0.5f, -0.5f, -0.5f), float4(1.f, 1.f, 1.f, 1.f) },//white
		{ float3(-0.5f, +0.5f, -0.5f), float4(0.f, 1.f, 1.f, 1.f) },//black
		{ float3(+0.5f, +0.5f, -0.5f), float4(1.f, 0.f, 1.f, 1.f) },//red
		{ float3(+0.5f, -0.5f, -0.5f), float4(1.f, 1.f, 0.f, 1.f) },//green
		{ float3(-0.5f, -0.5f, +0.5f), float4(0.f, 0.f, 1.f, 1.f) },//blue
		{ float3(-0.5f, +0.5f, +0.5f), float4(1.f, 0.f, 0.f, 1.f) },//yellow
		{ float3(+0.5f, +0.5f, +0.5f), float4(0.f, 1.f, 0.f, 1.f) },//cyan
		{ float3(+0.5f, -0.5f, +0.5f), float4(0.f, 0.f, 0.f, 1.f) }//magenta
	};

	// Create a cube
  //    v5----- v2
  //   /|      /|
  //  v6------v1|
  //  | |     | |
  //  | |v4---|-|v3
  //  |/      |/
  //  v7------v0
	//float3 pos, float3 normal, float3 tangent, float2 texXoord
	VertexNormalTangentTex TestBoxPNTT[24] =
	{
		//右侧面
		{ float3(+0.5f, -0.5f, -0.5f), float3(1.f, 0.f, 0.f), float3(0.f, 0.f, 1.f), float2(0.f, 1.f) },//0-0
		{ float3(+0.5f, +0.5f, -0.5f), float3(1.f, 0.f, 0.f), float3(0.f, 0.f, 1.f), float2(0.f, 0.f) },//1-1
		{ float3(+0.5f, +0.5f, +0.5f), float3(1.f, 0.f, 0.f), float3(0.f, 0.f, 1.f), float2(1.f, 0.f) },//2-2
		{ float3(+0.5f, -0.5f, +0.5f), float3(1.f, 0.f, 0.f), float3(0.f, 0.f, 1.f), float2(1.f, 1.f) },//3-3

		//左侧面
		{ float3(-0.5f, -0.5f, 0.5f), float3(-1.f, 0.f, 0.f), float3(0.f, 0.f, -1.f), float2(0.f, 1.f) },//4-4
		{ float3(-0.5f, 0.5f, 0.5f), float3(-1.f, 0.f, 0.f), float3(0.f, 0.f, -1.f), float2(0.f, 0.f) },//5-5
		{ float3(-0.5f, 0.5f, -0.5f), float3(-1.f, 0.f, 0.f), float3(0.f, 0.f, -1.f), float2(1.f, 0.f) },//6-6
		{ float3(-0.5f, -0.5f, -0.5f), float3(-1.f, 0.f, 0.f), float3(0.f, 0.f, -1.f), float2(1.f, 1.f) },//7-7

		//上面
		{ float3(-0.5f, 0.5f, -0.5f), float3(0.f, 1.f, 0.f), float3(1.f, 0.f, 0.f), float2(0.f, 1.f) },//8-6
		{ float3(-0.5f, 0.5f, 0.5f), float3(0.f, 1.f, 0.f), float3(1.f, 0.f, 0.f), float2(0.f, 0.f) },//9-5
		{ float3(0.5f, 0.5f, 0.5f), float3(0.f, 1.f, 0.f), float3(1.f, 0.f, 0.f), float2(1.f, 0.f) },//10-2
		{ float3(0.5f, 0.5f, -0.5f), float3(0.f, 1.f, 0.f), float3(1.f, 0.f, 0.f), float2(1.f, 1.f) },//11-1

		//底面
		{ float3(-0.5f, -0.5f, 0.5f), float3(0.f, -1.f, 0.f), float3(1.f, 0.f, 0.f), float2(0.f, 1.f) },//12-4
		{ float3(-0.5f, -0.5f, -0.5f), float3(0.f, -1.f, 0.f), float3(1.f, 0.f, 0.f), float2(0.f, 0.f) },//13-7
		{ float3(0.5f, -0.5f, -0.5f), float3(0.f, -1.f, 0.f), float3(1.f, 0.f, 0.f), float2(1.f, 0.f) },//14-0
		{ float3(0.5f, -0.5f, 0.5f), float3(0.f, -1.f, 0.f), float3(1.f, 0.f, 0.f), float2(1.f, 1.f) },//15-3

		//背面
		{ float3(0.5f, -0.5f, 0.5f), float3(0.f, 0.f, 1.f), float3(-1.f, 0.f, 0.f), float2(0.f, 1.f) },//16-3
		{ float3(0.5f, 0.5f, 0.5f), float3(0.f, 0.f, 1.f), float3(-1.f, 0.f, 0.f), float2(0.f, 0.f) },//17-2
		{ float3(-0.5f, 0.5f, 0.5f), float3(0.f, 0.f, 1.f), float3(-1.f, 0.f, 0.f), float2(1.f, 0.f) },//18-5
		{ float3(-0.5f, -0.5f, 0.5f), float3(0.f, 0.f, 1.f), float3(-1.f, 0.f, 0.f), float2(1.f, 1.f) },//19-4

		//前面
		{ float3(-0.5f, -0.5f, -0.5f), float3(0.f, 0.f, -1.f), float3(1.f, 0.f, 0.f), float2(0.f, 1.f) },//20-7
		{ float3(-0.5f, 0.5f, -0.5f), float3(0.f, 0.f, -1.f), float3(1.f, 0.f, 0.f), float2(0.f, 0.f) },//21-6
		{ float3(0.5f, 0.5f, -0.5f), float3(0.f, 0.f, -1.f), float3(1.f, 0.f, 0.f), float2(1.f, 0.f) },//22-1
		{ float3(0.5f, -0.5f, -0.5f), float3(0.f, 0.f, -1.f), float3(1.f, 0.f, 0.f), float2(1.f, 1.f) }//23-0

	};

	unsigned int TestBoxIndices[36] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	unsigned int NormalBoxIndices[36] = {
		// front face
		0, 2, 1,
		0, 2, 3,

		// back face
		4, 5, 6,
		4, 6, 7,

		// left face
		8, 9, 10,
		8, 10, 11,

		// right face
		12, 13, 14,
		12, 14, 15,

		// top face
		16, 17, 18,
		16, 18, 19,

		// bottom face
		20, 21, 22,
		20, 22, 23
	};

	D3D11_INPUT_ELEMENT_DESC SolidColorLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	D3D11_INPUT_ELEMENT_DESC TestBoxLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3D11_INPUT_ELEMENT_DESC VertextNormalTangentTexcoordLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};


}

