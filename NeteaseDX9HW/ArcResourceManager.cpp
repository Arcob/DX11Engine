#include "ArcResourceManager.h"

namespace DX11Engine {

	bool ArcResourceManager::CompileD3DShader(std::string filePath, char* entry, char* shaderModel, ID3DBlob** buffer) {
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined _DEBUG || defined DEBUG
		shaderFlags = D3DCOMPILE_DEBUG;
#endif

		ID3DBlob *errorBuffer = 0;
		HRESULT result;

		result = D3DX11CompileFromFile(ArcTool::stringToLPCWSTR(filePath), 0, 0, entry, shaderModel, shaderFlags, 0, 0, buffer, &errorBuffer, 0);

		if (FAILED(result))
		{
			if (errorBuffer != 0)
			{
				OutputDebugString((LPCWSTR)errorBuffer->GetBufferPointer());
				errorBuffer->Release();
			}
			return false;
		}

		if (errorBuffer != 0)
		{
			return false;
		}

		return true;
	}

	bool ArcResourceManager::LoadVertexShader(ID3D11Device* pd3dDevice, std::string filePath, char* entry, char* shaderModel, ID3DBlob *shaderBuffer, ID3D11VertexShader* vertexShader) {
		bool compileResult = CompileD3DShader(filePath, entry, shaderModel, &shaderBuffer);
		if (!compileResult)
		{
			MessageBox(0, L"载入顶点着色器错误", L"编译错误", MB_OK);
			return false;
		}

		long result;
		result = pd3dDevice->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(),
			0, &vertexShader);

		if (FAILED(result))
		{
			if (shaderBuffer)
			{
				shaderBuffer->Release();
			}
			return false;
		}

		return true;
	}

	bool ArcResourceManager::LoadPixelShader(ID3D11Device* pd3dDevice, std::string filePath, char* entry, char* shaderModel, ID3DBlob *shaderBuffer, ID3D11PixelShader* pixelShader) {
		bool compileResult = CompileD3DShader(filePath, entry, shaderModel, &shaderBuffer);
		if (!compileResult)
		{
			MessageBox(0, L"载入像素着色器错误", L"编译错误", MB_OK);
			return false;
		}

		long result;
		result = pd3dDevice->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(),
			0, &pixelShader);

		if (FAILED(result))
		{
			if (shaderBuffer)
			{
				shaderBuffer->Release();
			}
			return false;
		}

		return true;
	}

	bool ArcResourceManager::ConfigInputLayout(ID3D11Device* pd3dDevice, D3D11_INPUT_ELEMENT_DESC* inputLayout, unsigned int inputLayoutNum, ID3DBlob* shaderBuffer, ID3D11InputLayout* pInputLayout) {
		long result = pd3dDevice->CreateInputLayout(inputLayout, inputLayoutNum, shaderBuffer->GetBufferPointer(),
			shaderBuffer->GetBufferSize(), &pInputLayout);
		shaderBuffer->Release(); //传递完InputLayout之后shaderBuffer就没用了，此时释放shaderbuffer

		if (FAILED(result))
		{
			return false;
		}

		return true;
	}
}