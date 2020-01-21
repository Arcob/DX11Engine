#include "RacingGameAssets.h"
#include "SimpleVertexs.h"
#include "ArcStructures.h"
#include "ArcMath.h"
#include "ArcRHI.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"
#include "SimpleVertexs.h"
#include "ArcAssetLoader.h"

#include "ArcGraphicSetting.h"

#ifdef USING_DX11_ARC

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>
#include "D3DCompiler.h"

#endif // USING_DX11

RacingGameAssets::RacingGameAssets() : ArcAssets() {
	Load();
}

bool RacingGameAssets::Load() {
	//print("Load RacingGameAssets");

	std::shared_ptr<DX11Engine::ArcMesh> pBoxMesh = DX11Engine::ArcAssetLoader::LoadMesh("Box Mesh", DX11Engine::TestBoxVertices, sizeof(DX11Engine::Vertex), 8, DX11Engine::TestBoxIndices, 36, nullptr);
	if (pBoxMesh == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(std::move(pBoxMesh));//mesh的引用可能出问题

	//print(DX11Engine::TestBoxPNTT);
	std::shared_ptr<DX11Engine::ArcMesh> pBoxMeshWithNormal = DX11Engine::ArcAssetLoader::LoadMesh("Normal Box Mesh", DX11Engine::TestBoxPNTT, sizeof(DX11Engine::VertexNormalTangentTex), 24, DX11Engine::NormalBoxIndices, 36, nullptr);
	if (pBoxMeshWithNormal == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(std::move(pBoxMeshWithNormal));

	//三角形材质
	ID3DBlob *vertexShaderBuffer(0);
	ID3D11VertexShader* vertexShader(0);
	ID3DBlob *pixelShaderBuffer(0);
	ID3D11PixelShader* pixelShader(0);
	ID3D11InputLayout *inputLayout(0);

	std::string shaderPath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "SimpleShader.fx";
	if (!(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath, "VS_Main", "vs_4_0", &vertexShaderBuffer, &vertexShader))) {
		print("Vertex Shader Wrong");
		return false;
	}
	if (!(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::SolidColorLayout, ARRAYSIZE(DX11Engine::SolidColorLayout), &vertexShaderBuffer, &inputLayout))) {
		print("Config Input Layout Wrong");
		return false;
	}

	if (!(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath, "PS_Main", "ps_4_0", &pixelShaderBuffer, &pixelShader))) {
		print("Pixel Shader Wrong");
		return false;
	}
	std::shared_ptr<DX11Engine::ArcMaterial> simpleMaterial = std::make_shared<DX11Engine::ArcMaterial>("SimpleMaterial", vertexShader, pixelShader, inputLayout, nullptr, nullptr);
	ArcAssets::m_materialVector.push_back(std::move(simpleMaterial));

	//五彩正方形材质
	ID3DBlob *vertexShaderBuffer2(0);
	ID3D11VertexShader* vertexShader2(0);
	ID3DBlob *pixelShaderBuffer2(0);
	ID3D11PixelShader* pixelShader2(0);
	ID3D11InputLayout *inputLayout2(0);

	std::string shaderPath2 = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "TestBoxShader.fx";
	if (!(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath2, "VS", "vs_4_0", &vertexShaderBuffer2, &vertexShader2))) {
		print("Vertex Shader Wrong");
		return false;
	}
	if (!(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::TestBoxLayout, ARRAYSIZE(DX11Engine::TestBoxLayout), &vertexShaderBuffer2, &inputLayout2))) {
		print("Config Input Layout Wrong");
		return false;
	}

	if (!(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath2, "PS", "ps_4_0", &pixelShaderBuffer2, &pixelShader2))) {
		print("Pixel Shader Wrong");
		return false;
	}

	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(DX11Engine::ConstantBufferMvp);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Buffer* tempConstantBuffer = NULL;
	long hr = DX11Engine::ArcRHI::g_pd3dDevice->CreateBuffer(&cbDesc, NULL, &tempConstantBuffer);

	if (FAILED(hr)) {
		print("MVP Constant Buffer Wrong");
		return false;
	}

	ID3D11Buffer* lightConstantBuffer = NULL;
	hr = DX11Engine::ArcRHI::g_pd3dDevice->CreateBuffer(&cbDesc, NULL, &lightConstantBuffer);

	if (FAILED(hr)) {
		print("MVP Constant Buffer Wrong");
		return false;
	}
		
	std::shared_ptr<DX11Engine::ArcMaterial> TestBoxMaterial = std::make_shared<DX11Engine::ArcMaterial>("TestBoxMaterial", vertexShader2, pixelShader2, inputLayout2, tempConstantBuffer, lightConstantBuffer);
	ArcAssets::m_materialVector.push_back(std::move(TestBoxMaterial));

	//带贴图光照正方形材质
	ID3DBlob *vertexShaderBuffer3(0);
	ID3D11VertexShader* vertexShader3(0);
	ID3DBlob *pixelShaderBuffer3(0);
	ID3D11PixelShader* pixelShader3(0);
	ID3D11InputLayout *inputLayout3(0);

	std::string shaderPath3 = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "StandardShader.fx";
	if (!(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath3, "VS", "vs_4_0", &vertexShaderBuffer3, &vertexShader3))) {
		print("Vertex Shader Wrong");
		return false;
	}
	if (!(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::VertextNormalTangentTexcoordLayout, ARRAYSIZE(DX11Engine::VertextNormalTangentTexcoordLayout), &vertexShaderBuffer3, &inputLayout3))) {
		print("Config Input Layout Wrong");
		return false;
	}
	if (!(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath3, "PS", "ps_4_0", &pixelShaderBuffer3, &pixelShader3))) {
		print("Pixel Shader Wrong");
		return false;
	}

	D3D11_BUFFER_DESC cbDesc3;
	ZeroMemory(&cbDesc3, sizeof(cbDesc3));
	cbDesc3.ByteWidth = sizeof(DX11Engine::ConstantBufferMvp);
	cbDesc3.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc3.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc3.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Buffer* tempConstantBuffer3 = NULL;
	long hr3 = DX11Engine::ArcRHI::g_pd3dDevice->CreateBuffer(&cbDesc3, NULL, &tempConstantBuffer3);

	if (FAILED(hr3)) {
		print("MVP Constant Buffer Wrong");
		return false;
	}

	ID3D11Buffer* lightConstantBuffer3 = NULL;
	hr3 = DX11Engine::ArcRHI::g_pd3dDevice->CreateBuffer(&cbDesc3, NULL, &lightConstantBuffer3);

	if (FAILED(hr3)) {
		print("MVP Constant Buffer Wrong");
		return false;
	}

	std::shared_ptr<DX11Engine::ArcMaterial> StandardMaterial = std::make_shared<DX11Engine::ArcMaterial>("StandardMaterial", vertexShader3, pixelShader3, inputLayout3, tempConstantBuffer3, lightConstantBuffer3);
	ArcAssets::m_materialVector.push_back(std::move(StandardMaterial));

	std::string texturePath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::TEXTURE_PATH + "WoodCrate.dds";
	auto boxTexture = DX11Engine::ArcAssetLoader::LoadTexture("BoxTexture", texturePath);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	DX11Engine::ArcRHI::g_pd3dDevice->CreateSamplerState(&sampDesc, &(boxTexture->m_sampleState));

	DX11Engine::ArcRHI::g_pImmediateContext->PSSetShaderResources(0, 1, &(boxTexture->m_textureView));//贴图绑定
	DX11Engine::ArcRHI::g_pImmediateContext->PSSetSamplers(0, 1, &(boxTexture->m_sampleState));//采样状态绑定
	
	return true;
}
