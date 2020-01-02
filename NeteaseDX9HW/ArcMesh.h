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

namespace DX11Engine { //跨平台弃疗了,强相关
	class ArcMesh
	{
	public:
		ArcMesh(std::string meshName, std::shared_ptr<ID3D11Buffer> vertexBuffer, std::shared_ptr <ID3D11Buffer> indexBuffer, std::shared_ptr <ID3D11InputLayout> inputLayout);
		~ArcMesh() = default;
	private:
		std::string m_meshName;
		std::shared_ptr<ID3D11Buffer> m_pVertexBuffer;//顶点缓冲
		std::shared_ptr <ID3D11Buffer> m_pIndexBuffer;//顶点索引缓冲
		std::shared_ptr <ID3D11InputLayout> m_pInputLayout;
	};

}

