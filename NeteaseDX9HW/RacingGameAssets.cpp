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
	std::shared_ptr<DX11Engine::ArcMaterial> simpleMaterial = std::make_shared<DX11Engine::ArcMaterial>("SimpleMaterial", vertexShader, pixelShader, inputLayout);
	ArcAssets::m_materialVector.push_back(std::move(simpleMaterial));
	//buffer没release

	return true;
}
