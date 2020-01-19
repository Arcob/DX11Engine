#pragma once

#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"
#include "ArcTool.h"


#ifdef USING_DX11_ARC

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>

#endif // USING_DX11

namespace DX11Engine {

	class ArcTexture
	{
	public:
		ArcTexture(std::string name);
		~ArcTexture() = default;

		std::string m_name;
		ID3D11Resource* m_texture;               //指向资源接口类的指针，也可以填nullptr
		ID3D11ShaderResourceView* m_textureView; //指向着色器资源视图的指针，也可以填nullptr
	};

}

