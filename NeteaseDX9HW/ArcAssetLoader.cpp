#include "ArcAssetLoader.h"
#include "ArcTool.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

namespace DX11Engine {
	const std::string ArcAssetLoader::SHADER_PATH = "\\NeteaseDX9HW\\Shaders\\";
	const std::string ArcAssetLoader::TEXTURE_PATH = "\\NeteaseDX9HW\\Textures\\";
	const std::string ArcAssetLoader::MODEL_PATH = "\\NeteaseDX9HW\\Models\\";

	std::shared_ptr<DirectX::EffectFactory> ArcAssetLoader::m_fxFactory = nullptr;

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
		//ArcRHI::g_pImmediateContext->IASetInputLayout(*pInputLayout);
		(*shaderBuffer)->Release(); //传递完InputLayout之后shaderBuffer就没用了，此时释放shaderbuffer

		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	std::shared_ptr<ArcMesh> ArcAssetLoader::LoadMesh(std::string name, void* vertexs, unsigned int nodeLength, unsigned int nodeCount, unsigned int* indices, unsigned int indicesLength, ID3D11InputLayout *inputLayout) {
		std::shared_ptr<DX11Engine::ArcMesh> pTempMesh = std::make_shared<DX11Engine::ArcMesh>(name, ArcRHI::g_pd3dDevice);
		pTempMesh->m_nodeLength = nodeLength;
		pTempMesh->m_nodeCount = nodeCount;
		if (!pTempMesh->BindVertexBuffer(vertexs, nodeLength * nodeCount)) {
			return nullptr;
		}

		if (!pTempMesh->BindIndexBuffer(indices, indicesLength)) {
			return nullptr;
		}

		pTempMesh->m_pInputLayout = inputLayout;
		return std::move(pTempMesh);
	}
	//$(ProjectDir)Common
	std::shared_ptr<ArcTexture> ArcAssetLoader::LoadTexture(std::string textureName, std::string path) {
		auto texture = std::make_shared<ArcTexture>(textureName);
		long result = DirectX::CreateDDSTextureFromFile(ArcRHI::g_pd3dDevice, ArcTool::stringToLPCWSTR(path), &(texture->m_texture), &(texture->m_textureView));
		if (FAILED(result))
		{
			MessageBox(nullptr, L"create texture failed!", L"error", MB_OK);
			return nullptr;
		}
		return texture;
	}

	bool ArcAssetLoader::CreateConstantBuffer(ID3D11Device* device, D3D11_BUFFER_DESC* description, ID3D11Buffer** constantBuffer) {
		long hr3 = device->CreateBuffer(description, NULL, constantBuffer);

		if (FAILED(hr3)) {
			print("MVP Constant Buffer Wrong");
			return false;
		}
		return true;
	}

	void ArcAssetLoader::SetTexture(D3D11_SAMPLER_DESC* sampDescription, std::shared_ptr<ArcTexture> texture, unsigned int textureSlot, unsigned int descSlot) {
		ArcRHI::g_pd3dDevice->CreateSamplerState(sampDescription, &(texture->m_sampleState));
		ArcRHI::g_pImmediateContext->PSSetShaderResources(textureSlot, 1, &(texture->m_textureView));//贴图绑定
		ArcRHI::g_pImmediateContext->PSSetSamplers(descSlot, 1, &(texture->m_sampleState));//采样状态绑定
	}

	std::unique_ptr<DirectX::Model> ArcAssetLoader::LoadModelFormFileInner(std::string path) {
		if (m_fxFactory == nullptr) {
			m_fxFactory = std::make_shared<DirectX::EffectFactory>(ArcRHI::g_pd3dDevice);
		}
		return DirectX::Model::CreateFromCMO(ArcRHI::g_pd3dDevice, ArcTool::stringToLPCWSTR(path), *m_fxFactory);
	}

	std::shared_ptr<ArcMesh> ArcAssetLoader::LoadModelFormFile(std::string name, std::string path) {
		auto dxModelTypeMesh = LoadModelFormFileInner(path);
		std::shared_ptr<DX11Engine::ArcMesh> pTempMesh = std::make_shared<DX11Engine::ArcMesh>(name, ArcRHI::g_pd3dDevice);
		auto innerModelData = dxModelTypeMesh->meshes[0];// ->meshParts;
		pTempMesh->m_pVertexBuffer = innerModelData->meshParts[0]->vertexBuffer.Get();
		innerModelData->meshParts[0]->vertexBuffer.Detach();
		//print(dxModelTypeMesh->meshes.size());
		//print(innerModelData->meshParts.size());
		print("m_pVertexBuffer: " << pTempMesh->m_pVertexBuffer);
		pTempMesh->m_nodeLength = innerModelData->meshParts[0]->vertexStride;
		print("m_nodeLength: " << pTempMesh->m_nodeLength);
		//pTempMesh->m_nodeCount = innerModelData->meshParts[0]->vertexOffset;//??
		//print("m_nodeCount: " << pTempMesh->m_nodeCount);
		pTempMesh->m_pIndexBuffer = innerModelData->meshParts[0]->indexBuffer.Get();
		innerModelData->meshParts[0]->indexBuffer.Detach();
		print("m_pIndexBuffer : " << pTempMesh->m_pIndexBuffer);
		pTempMesh->m_indexLength = innerModelData->meshParts[0]->indexCount;
		print("m_indexLength : " << pTempMesh->m_indexLength);
		pTempMesh->m_pInputLayout = innerModelData->meshParts[0]->inputLayout.Get();
		innerModelData->meshParts[0]->inputLayout.Detach();
		print("m_pInputLayout : " << pTempMesh->m_pInputLayout);
		
		return pTempMesh;
	}

	std::shared_ptr<ArcMesh> ArcAssetLoader::LoadModelFormObj(std::string name, std::string path) {
		std::cout << "Loading " << path << std::endl;

		tinyobj::attrib_t attrib; // 所有的数据放在这里
		std::vector<tinyobj::shape_t> shapes;
		// 一个shape,表示一个部分,
		// 其中主要存的是索引坐标 mesh_t类,
		// 放在indices中
		/*
		// -1 means not used.
		typedef struct {
		  int vertex_index;
		  int normal_index;
		  int texcoord_index;
		} index_t;
		*/
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

		// 接下里就是从上面的属性中取值了
		if (!warn.empty()) {
			std::cout << "WARN: " << warn << std::endl;
		}

		if (!err.empty()) {
			std::cerr << "ERR: " << err << std::endl;
		}

		if (!ret) {
			printf("Failed to load/parse .obj.\n");
			return false;
		}

	}
}