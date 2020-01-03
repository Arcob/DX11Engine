#include "ArcAssetLoader.h"
#include "ArcTool.h"

namespace DX11Engine {
	const std::string ArcAssetLoader::SHADER_PATH = "\\NeteaseDX9HW\\Shaders\\";

	bool ArcAssetLoader::CompileD3DShader(std::string filePath, const char* entry, const char* shaderModel, ID3DBlob** buffer) {
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

	bool ArcAssetLoader::LoadVertexShader(std::string filePath, const char* entry, const char* shaderModel, ID3DBlob **shaderBuffer, ID3D11VertexShader** vertexShader) {
		bool compileResult = CompileD3DShader(filePath, entry, shaderModel, shaderBuffer);
		if (!compileResult)
		{
			MessageBox(0, L"载入顶点着色器错误", L"编译错误", MB_OK);
			return false;
		}

		long result;
		result = ArcRHI::g_pd3dDevice->CreateVertexShader((*shaderBuffer)->GetBufferPointer(), (*shaderBuffer)->GetBufferSize(),
			0, vertexShader);

		if (FAILED(result))
		{
			if (*shaderBuffer)
			{
				(*shaderBuffer)->Release();
			}
			return false;
		}
		return true;
	}

	bool ArcAssetLoader::LoadPixelShader(std::string filePath, const char* entry, const char* shaderModel, ID3DBlob **shaderBuffer, ID3D11PixelShader **pixelShader) {
		bool compileResult = CompileD3DShader(filePath, entry, shaderModel, shaderBuffer);
		if (!compileResult)
		{
			MessageBox(0, L"载入像素着色器错误", L"编译错误", MB_OK);
			return false;
		}

		long result;
		result = ArcRHI::g_pd3dDevice->CreatePixelShader((*shaderBuffer)->GetBufferPointer(), (*shaderBuffer)->GetBufferSize(),
			0, pixelShader);

		if (FAILED(result))
		{
			if (*shaderBuffer)
			{
				(*shaderBuffer)->Release();
			}
			return false;
		}

		return true;
	}

	bool ArcAssetLoader::ConfigInputLayout(D3D11_INPUT_ELEMENT_DESC* inputLayout, unsigned int inputLayoutNum, ID3DBlob **shaderBuffer, ID3D11InputLayout **pInputLayout) {
		long result = ArcRHI::g_pd3dDevice->CreateInputLayout(inputLayout, inputLayoutNum, (*shaderBuffer)->GetBufferPointer(),
			(*shaderBuffer)->GetBufferSize(), pInputLayout);
		(*shaderBuffer)->Release(); //传递完InputLayout之后shaderBuffer就没用了，此时释放shaderbuffer

		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	std::shared_ptr<ArcMesh> ArcAssetLoader::LoadMesh(std::string name, Vertex* vertexs, unsigned int vertexsLength, unsigned int* indices, unsigned int indicesLength) {
		std::shared_ptr<DX11Engine::ArcMesh> pBoxMesh = std::make_shared<DX11Engine::ArcMesh>(name, ArcRHI::g_pd3dDevice);

		if (!pBoxMesh->BindVertexBuffer(vertexs, vertexsLength)) {
			return nullptr;
		}

		if (!pBoxMesh->BindIndexBuffer(indices, indicesLength)) {
			return nullptr;
		}

		return std::move(pBoxMesh);
	}
}