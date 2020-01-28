#pragma once

#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"
#include "ArcTool.h"
#include "ArcStructures.h"
#include "ArcRHI.h"
#include "ArcMesh.h"
#include "ArcTexture.h"
#include "Model.h"
#include "Effects.h"

#ifdef USING_DX11_ARC

#include <d3d11.h>
#include <d3dx11.h>
#include <direct.h>
#include "D3DCompiler.h"


#endif // USING_DX11

namespace DX11Engine {

	class ArcAssetLoader //跨平台强相关，用于加载shader，texture，mesh等多种资源,加载好的资源存到ArcAsset中
	{
	public:
		//shader	
		static bool LoadVertexShader(std::string filePath, const char* entry, const char* shaderModel, ID3DBlob **shaderBuffer, ID3D11VertexShader** vertexShader);
		static bool LoadPixelShader(std::string filePath, const char* entry, const char* shaderModel, ID3DBlob **shaderBuffer, ID3D11PixelShader **pixelShader);
		static bool ConfigInputLayout(D3D11_INPUT_ELEMENT_DESC* inputLayout, unsigned int inputLayoutNum, ID3DBlob **shaderBuffer, ID3D11InputLayout **pInputLayout);
		static std::shared_ptr<ArcMesh> LoadMesh(std::string name, void* vertexs, unsigned int nodeLength, unsigned int nodeCount, unsigned int* indices, unsigned int indicesLength, ID3D11InputLayout *pInputLayout);
		static std::shared_ptr<ArcTexture> LoadTexture(std::string name, std::string path);
		static bool CreateConstantBuffer(ID3D11Device* device, D3D11_BUFFER_DESC* description, ID3D11Buffer** constantBuffer);
		static void SetTexture(D3D11_SAMPLER_DESC* sampDescription, std::shared_ptr<ArcTexture> texture, unsigned int textureSlot, unsigned int descSlot);	
		static std::shared_ptr<ArcMesh> LoadModelFormFile(std::string name, std::string path);
		static std::unique_ptr<DirectX::Model> LoadModelFormFileInner(std::string name);
		const static std::string SHADER_PATH;
		const static std::string TEXTURE_PATH;
		const static std::string MODEL_PATH;
	private:
		
		static std::shared_ptr<DirectX::EffectFactory> m_fxFactory;
		static bool CompileD3DShader(std::string filePath, const char* entry, const char* shaderModel, ID3DBlob** buffer);
	};
};
