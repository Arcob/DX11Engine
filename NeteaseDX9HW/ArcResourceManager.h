#pragma once
#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"
#include "ArcTool.h"

#ifdef USING_DX11

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>
#include "D3DCompiler.h"

#endif // USING_DX11

namespace DX11Engine {

	class ArcResourceManager //跨平台强相关，用于加载shader，textire，mesh等多种资源
	{
	public:
		//shader	
		static bool LoadVertexShader(ID3D11Device* pd3dDevice, std::string filePath, char* entry, char* shaderModel, ID3DBlob *shaderBuffer, ID3D11VertexShader* vertexShader);
		static bool LoadPixelShader(ID3D11Device* pd3dDevice, std::string filePath, char* entry, char* shaderModel, ID3DBlob *shaderBuffer, ID3D11PixelShader* vertexShader);
		static bool ConfigInputLayout(ID3D11Device* pd3dDevice, D3D11_INPUT_ELEMENT_DESC* inputLayout, unsigned int inputLayoutNum, ID3DBlob* shaderBuffer, ID3D11InputLayout* pInputLayout);

	private:
		static bool CompileD3DShader(std::string filePath, char* entry, char* shaderModel, ID3DBlob** buffer);
	};
}
