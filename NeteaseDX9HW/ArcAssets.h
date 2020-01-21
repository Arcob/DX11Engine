#pragma once

#include "CommonHeaders.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"

namespace DX11Engine {

	class ArcAssets
	{
	public:
		ArcAssets();
		virtual ~ArcAssets() = default;
		virtual bool Load();
		std::shared_ptr<DX11Engine::ArcMesh> findMesh(std::string name);
		std::shared_ptr<DX11Engine::ArcMaterial> findMaterial(std::string name);

		std::vector<std::shared_ptr<DX11Engine::ArcMesh>> m_meshVector;
		std::vector<std::shared_ptr<DX11Engine::ArcMaterial>> m_materialVector;
	private:
		
		//class ID3D11Device* m_pDevice; //device指针强转过来的
	};

	struct MaterialInitStruct {
	public:
		MaterialInitStruct() : m_vertexShaderBuffer(0), m_vertexShader(0), m_pixelShaderBuffer(0), m_pixelShader(0), m_inputLayout(0){}

		ID3DBlob *m_vertexShaderBuffer;
		ID3D11VertexShader* m_vertexShader;
		ID3DBlob *m_pixelShaderBuffer;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout *m_inputLayout;

	};

}

