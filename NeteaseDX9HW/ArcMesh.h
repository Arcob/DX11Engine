#pragma once

#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"

#ifdef USING_DX11

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>
#include "D3DCompiler.h"
#include "d3dx11effect.h"

#endif // USING_DX11

namespace DX11Engine { //��ƽ̨������,ǿ���
	class ArcMesh
	{
	public:
		ArcMesh(std::string meshName, std::shared_ptr<ID3D11Buffer> vertexBuffer, std::shared_ptr <ID3D11Buffer> indexBuffer, std::shared_ptr <ID3D11InputLayout> inputLayout);
		~ArcMesh() = default;
	private:
		std::string m_meshName;
		std::shared_ptr<ID3D11Buffer> m_pVertexBuffer;//���㻺��
		std::shared_ptr <ID3D11Buffer> m_pIndexBuffer;//������������
		std::shared_ptr <ID3D11InputLayout> m_pInputLayout;
	};

}

