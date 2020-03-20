#include "ShadowAssets.h"
#include "SimpleVertexs.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"
#include "ArcAssetLoader.h"
#include "ArcGeometryGenerator.h"

ShadowAssets::ShadowAssets() : ArcAssets() {
	//Load();
}

/* 加载的资源名称：
Mesh:
	Generated Box Mesh

Material:
	StandardMaterial

Texture:
	WoodTexture
	MarbleTexture
*/

bool ShadowAssets::Load() {

#pragma region LoadMeshRegion
	std::shared_ptr<ArcGeometryGenerator::MeshData> generatedCubeMeshData = std::make_shared<ArcGeometryGenerator::MeshData>();
	ArcGeometryGenerator::CreateBox(1.f, 1.f, 1.f, *generatedCubeMeshData);
	std::shared_ptr<DX11Engine::ArcMesh> pGeneratedBoxMesh = DX11Engine::ArcAssetLoader::LoadMesh("Generated Box Mesh", generatedCubeMeshData->vertices.data(), sizeof(DX11Engine::VertexNormalTangentTex), generatedCubeMeshData->vertices.size(), generatedCubeMeshData->indices.data(), generatedCubeMeshData->indices.size(), nullptr);
	if (pGeneratedBoxMesh == nullptr) print("Unable to load mesh");
	ArcAssets::m_meshVector.push_back(std::move(pGeneratedBoxMesh));
#pragma endregion

#pragma region LoadTextureRegion
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MaxAnisotropy = 4;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	std::string woodTexturePath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::TEXTURE_PATH + "HDWood.dds";
	auto woodTexture = DX11Engine::ArcAssetLoader::LoadTexture("WoodTexture", woodTexturePath);

	std::string marbleTexturePath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::TEXTURE_PATH + "HDMarble.dds";
	auto marbleTexture = DX11Engine::ArcAssetLoader::LoadTexture("MarbleTexture", marbleTexturePath);

	//将贴图和slot一一对应
	DX11Engine::ArcAssetLoader::SetTexture(&sampDesc, woodTexture, 0, 0);
	DX11Engine::ArcAssetLoader::SetTexture(&sampDesc, marbleTexture, 1, 0);
#pragma endregion

#pragma region LoadMaterialRegion
	D3D11_BUFFER_DESC cbDescMVP;
	ZeroMemory(&cbDescMVP, sizeof(cbDescMVP));
	cbDescMVP.ByteWidth = sizeof(DX11Engine::ConstantBufferMvp);
	cbDescMVP.Usage = D3D11_USAGE_DYNAMIC;
	cbDescMVP.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDescMVP.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_BUFFER_DESC cbDescLight;
	ZeroMemory(&cbDescLight, sizeof(cbDescLight));
	cbDescLight.ByteWidth = sizeof(DX11Engine::ConstantBufferLight);
	cbDescLight.Usage = D3D11_USAGE_DYNAMIC;
	cbDescLight.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDescLight.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//带贴图光照正方形材质
	DX11Engine::MaterialInitStruct misStandardMat = DX11Engine::MaterialInitStruct();
	std::string shaderPath3 = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "StandardShader.fx";
	DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath3, "VS", "vs_4_0", &(misStandardMat.m_vertexShaderBuffer), &(misStandardMat.m_vertexShader));
	DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::VertextNormalTangentTexcoordLayout, ARRAYSIZE(DX11Engine::VertextNormalTangentTexcoordLayout), &(misStandardMat.m_vertexShaderBuffer), &(misStandardMat.m_inputLayout));
	DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath3, "PS", "ps_4_0", &(misStandardMat.m_pixelShaderBuffer), &(misStandardMat.m_pixelShader));

	ID3D11Buffer* tempConstantBuffer3 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescMVP, &tempConstantBuffer3);

	ID3D11Buffer* lightConstantBuffer3 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescLight, &lightConstantBuffer3);

	std::shared_ptr<DX11Engine::ArcMaterial> StandardMaterial = std::make_shared<DX11Engine::ArcMaterial>("StandardMaterial", misStandardMat.m_vertexShader, misStandardMat.m_pixelShader, misStandardMat.m_inputLayout, tempConstantBuffer3, lightConstantBuffer3);
	ArcAssets::m_materialVector.push_back(std::move(StandardMaterial));
#pragma endregion
	return true;
}