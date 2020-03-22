#include "ArcAssetLoader.h"
#include "ArcTool.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

namespace DX11Engine {
	const std::string ArcAssetLoader::SHADER_PATH = "\\NeteaseDX9HW\\Shaders\\";
	const std::string ArcAssetLoader::TEXTURE_PATH = "\\NeteaseDX9HW\\Textures\\";
	const std::string ArcAssetLoader::MODEL_PATH = "\\NeteaseDX9HW\\Models\\";

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
				print(std::string((char*)errorBuffer->GetBufferPointer()));
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

	std::shared_ptr<ArcMesh> ArcAssetLoader::LoadModelFromObj(std::string name, std::string fileName, std::string basePath) {
		//std::cout << "Loading " << fileName << std::endl;

		//std::shared_ptr<tinyobj::attrib_t> attrib; // 所有的数据放在这里
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, fileName.c_str(), basePath.c_str(), true);
		
		// 接下里就是从上面的属性中取值了
		if (!warn.empty()) {
			std::cout << "WARN: " << warn << std::endl;
		}

		if (!err.empty()) {
			std::cerr << "ERR: " << err << std::endl;
		}

		if (!ret) {
			printf("Failed to load/parse .obj.\n");
			return nullptr;
		}

		/*
		//int vertexSize = attrib.vertices.size();
		std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
		std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
		std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2)
			<< std::endl;

		std::cout << "# of shapes    : " << shapes.size() << std::endl;
		std::cout << "# of materials : " << materials.size() << std::endl;
		*/

		std::vector<VertexNormalTangentTex> vertexVec;
		std::vector<unsigned int> indicesVec;

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				VertexNormalTangentTex vertex = {};

				if (attrib.vertices.size() > 0) {
					vertex.pos = float3(attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1], attrib.vertices[3 * index.vertex_index + 2]);
					//PrintFloat3(vertex.pos);
				}

				if (attrib.normals.size() > 0) {
					vertex.normal = float3(attrib.normals[3 * index.normal_index + 0], attrib.normals[3 * index.normal_index + 1], attrib.normals[3 * index.normal_index + 2]);
					vertex.tangent = float3(0.0f, 1.0f, 0.0f);
				}
				else {
					vertex.normal = float3(1.0f, 0.0f, 0.0f);
					vertex.tangent = float3(0.0f, 1.0f, 0.0f);
				}


				if (attrib.texcoords.size() > 0) {
					vertex.texCoord = float2(attrib.texcoords[2 * index.texcoord_index + 0], 1.0f - attrib.texcoords[2 * index.texcoord_index + 1]);
				}
				else {
					vertex.texCoord = float2(0.9f, 0.9f);
				}
				
				vertexVec.push_back(vertex);
				indicesVec.push_back(indicesVec.size());
			}
		}

		std::shared_ptr<ArcMesh> result = LoadMesh(name, vertexVec.data(), sizeof(DX11Engine::VertexNormalTangentTex), vertexVec.size(), indicesVec.data(), indicesVec.size(), nullptr);

		return result;
	}
}