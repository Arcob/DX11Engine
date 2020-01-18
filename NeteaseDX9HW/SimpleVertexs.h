#pragma once

#include "CommonHeaders.h"
#include "ArcMath.h"
#include "ArcStructures.h"

namespace DX11Engine {
	Vertex TestBoxVertices[] =
	{
		{ float3(-0.5f, -0.5f, -0.5f), float4(255, 255, 255, 1) },//white
		{ float3(-0.5f, +0.5f, -0.5f), float4(0, 0, 0, 1) },//black
		{ float3(+0.5f, +0.5f, -0.5f), float4(255, 0, 0, 1) },//red
		{ float3(+0.5f, -0.5f, -0.5f), float4(0, 255, 0, 1) },//green
		{ float3(-0.5f, -0.5f, +0.5f), float4(0, 0, 255, 1) },//blue
		{ float3(-0.5f, +0.5f, +0.5f), float4(255, 255, 0, 1) },//yellow
		{ float3(+0.5f, +0.5f, +0.5f), float4(0, 255, 255, 1) },//cyan
		{ float3(+0.5f, -0.5f, +0.5f), float4(255, 0, 255, 1) }//magenta
	};

	unsigned int TestBoxIndices[] = {
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

	D3D11_INPUT_ELEMENT_DESC SolidColorLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	D3D11_INPUT_ELEMENT_DESC TestBoxLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3D11_INPUT_ELEMENT_DESC VertextNormalTextureLayout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
}

