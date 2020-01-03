#pragma once

#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"
#include "ArcStructures.h"

#ifdef USING_DX11

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>
#include "D3DCompiler.h"

#endif // USING_DX11

namespace DX11Engine { //��ƽ̨������,ǿ���
	class ArcMesh
	{
	public:
		//ArcMesh(std::string meshName, ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, ID3D11InputLayout* inputLayout);
		ArcMesh(std::string meshName, ID3D11Device* device);
		~ArcMesh() = default;
		bool BindVertexBuffer(Vertex* vertexs, unsigned int length);
		bool BindIndexBuffer(unsigned int* indices, unsigned int length);

		std::string m_meshName;
		ID3D11Device* m_device;
		ID3D11Buffer* m_pVertexBuffer;//���㻺��
		ID3D11Buffer* m_pIndexBuffer;//������������
		ID3D11InputLayout* m_pInputLayout;

	private:
		
	};

}
