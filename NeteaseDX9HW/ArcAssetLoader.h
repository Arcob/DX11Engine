#pragma once
#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"
#include "ArcTool.h"
#include "ArcStructures.h"
#include "ArcRHI.h"
#include "ArcMesh.h"

#ifdef USING_DX11

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>
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
		static std::shared_ptr<ArcMesh> LoadMesh(std::string name, Vertex* vertexs, unsigned int vertexsLength, unsigned int* indices, unsigned int indicesLength);
		const static std::string SHADER_PATH;
	private:
		static bool CompileD3DShader(std::string filePath, const char* entry, const char* shaderModel, ID3DBlob** buffer);
	};
}
