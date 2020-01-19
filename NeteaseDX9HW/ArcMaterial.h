#pragma once

#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"
#include "ArcTool.h"

#ifdef USING_DX11_ARC

#include <d3d11.h>
#include "D3DCompiler.h"

#endif

namespace DX11Engine {

	class ArcMaterial //平台强相关。。。跨平台先弃疗
	{
	public:
		ArcMaterial(std::string name, ID3D11VertexShader *pSolidColorVS, ID3D11PixelShader *pSolidColorPS, ID3D11InputLayout *pInputLayout, ID3D11Buffer* pMVPConstantBuffer);
		~ArcMaterial() = default;
		void ReleaseAllBuffers();

		std::string m_name;
		ID3D11InputLayout *m_pInputLayout;
		ID3D11VertexShader *m_pVertexShader;
		ID3D11PixelShader *m_pPixelShader;
		ID3D11Buffer* m_pMVPConstantBuffer;

	private:

	};

}

