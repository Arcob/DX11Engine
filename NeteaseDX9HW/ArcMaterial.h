#pragma once

#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"
#include "ArcTool.h"

#ifdef USING_DX11

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>
#include "D3DCompiler.h"

#endif

namespace DX11Engine {

	class ArcMaterial //平台强相关。。。抽象的有问题
	{
	public:
		ArcMaterial(ID3D11Buffer *pVertexBuffer, ID3D11InputLayout *pInputLayout, ID3D11VertexShader *pSolidColorVS, ID3D11PixelShader *pSolidColorPS);
		~ArcMaterial() = default;

	private:
		ID3D11Buffer *m_pVertexBuffer;
		ID3D11InputLayout *m_pInputLayout;
		ID3D11VertexShader *m_pSolidColorVS;
		ID3D11PixelShader *m_pSolidColorPS;
	};

}

