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
		ID3D11Resource* m_texture;               //ָ����Դ�ӿ����ָ�룬Ҳ������nullptr
		ID3D11ShaderResourceView* m_textureView; //ָ����ɫ����Դ��ͼ��ָ�룬Ҳ������nullptr
	};

}

