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

#ifdef USING_DX11

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

	std::shared_ptr<DX11Engine::ArcMesh> pBoxMesh = DX11Engine::ArcAssetLoader::LoadMesh("Box Mesh", DX11Engine::TestBoxVertices, 8, DX11Engine::TestBoxIndices, 36);
	if (pBoxMesh == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(std::move(pBoxMesh));//mesh的引用可能出问题

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
	std::shared_ptr<DX11Engine::ArcMaterial> simpleMaterial = std::make_shared<DX11Engine::ArcMaterial>("SimpleMaterial", vertexShader, pixelShader, inputLayout, nullptr);
	ArcAssets::m_materialVector.push_back(std::move(simpleMaterial));

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

	/*D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(DX11Engine::ConstantBuffer);
	//绑定信息是常量缓存
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;*/

	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(DX11Engine::ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cbDesc.MiscFlags = 0;
	//cbDesc.StructureByteStride = 0;

	ID3D11Buffer* tempConstantBuffer = NULL;
	long hr = DX11Engine::ArcRHI::g_pd3dDevice->CreateBuffer(&cbDesc, NULL, &tempConstantBuffer);

	if (FAILED(hr)) {
		print("MVP Constant Buffer Wrong");
		return false;
	}
		
	std::shared_ptr<DX11Engine::ArcMaterial> TestBoxMaterial = std::make_shared<DX11Engine::ArcMaterial>("TestBoxMaterial", vertexShader2, pixelShader2, inputLayout2, tempConstantBuffer);

	ArcAssets::m_materialVector.push_back(std::move(TestBoxMaterial));
	//buffer没release

	return true;
}
