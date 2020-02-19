#include "RacingGameAssets.h"
#include "SimpleVertexs.h"
#include "ArcStructures.h"
#include "ArcMath.h"
#include "ArcRHI.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"
#include "SimpleVertexs.h"
#include "ArcAssetLoader.h"
#include "ArcGeometryGenerator.h"

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
/* 加载的资源名称：
Mesh:
	Box Mesh
	Normal Box Mesh
	Sphere Mesh
	Cylinder Mesh
	Generated Box Mesh
	//Cat Mesh
	Cornell Box

Material:
	SimpleMaterial
	TestBoxMaterial
	StandardMaterial
	SkyBoxMaterial
	CatMaterial

Texture:
	BoxTexture
	SkyBoxTexture
*/

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

	std::shared_ptr<ArcGeometryGenerator::MeshData> sphereMeshData = std::make_shared<ArcGeometryGenerator::MeshData>();
	ArcGeometryGenerator::CreateSphere(0.3f, 30, 30, *sphereMeshData);
	std::shared_ptr<DX11Engine::ArcMesh> pSkyboxMesh = DX11Engine::ArcAssetLoader::LoadMesh("Sphere Mesh", sphereMeshData->vertices.data(), sizeof(DX11Engine::VertexNormalTangentTex), sphereMeshData->vertices.size(), sphereMeshData->indices.data(), sphereMeshData->indices.size(), nullptr);
	if (pSkyboxMesh == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(std::move(pSkyboxMesh));

	std::shared_ptr<ArcGeometryGenerator::MeshData> cylinderMeshData = std::make_shared<ArcGeometryGenerator::MeshData>();
	ArcGeometryGenerator::CreateCylinder(0.5f, 0.5f, 2, 20, 20, *cylinderMeshData);
	ArcGeometryGenerator::AddCylinderTopCap(0.5f, 0.5f, 2, 20, 20, *cylinderMeshData);
	ArcGeometryGenerator::AddCylinderBottomCap(0.5f, 0.5f, 2, 20, 20, *cylinderMeshData);
	std::shared_ptr<DX11Engine::ArcMesh> pCylinderMesh = DX11Engine::ArcAssetLoader::LoadMesh("Cylinder Mesh", cylinderMeshData->vertices.data(), sizeof(DX11Engine::VertexNormalTangentTex), cylinderMeshData->vertices.size(), cylinderMeshData->indices.data(), cylinderMeshData->indices.size(), nullptr);
	if (pCylinderMesh == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(std::move(pCylinderMesh));

	std::string objPath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::MODEL_PATH;
	std::string objName = "Stickman.obj";
	std::shared_ptr<DX11Engine::ArcMesh> pObjMesh = DX11Engine::ArcAssetLoader::LoadModelFromObj("Cornell Box", objPath + objName, objPath);
	if (pObjMesh == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(std::move(pObjMesh));

	/*std::string catMeshPath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::MODEL_PATH + "cat.cmo";
	std::shared_ptr<DX11Engine::ArcMesh> pCatMesh = DX11Engine::ArcAssetLoader::LoadModelFormFile("Cat Mesh", catMeshPath);
	if (pCatMesh == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(pCatMesh);//mesh的引用可能出问题*/

	std::shared_ptr<ArcGeometryGenerator::MeshData> generatedCubeMeshData = std::make_shared<ArcGeometryGenerator::MeshData>();
	ArcGeometryGenerator::CreateBox(1.f, 1.f, 1.f, *generatedCubeMeshData);
	std::shared_ptr<DX11Engine::ArcMesh> pGeneratedBoxMesh = DX11Engine::ArcAssetLoader::LoadMesh("Generated Box Mesh", generatedCubeMeshData->vertices.data(), sizeof(DX11Engine::VertexNormalTangentTex), generatedCubeMeshData->vertices.size(), generatedCubeMeshData->indices.data(), generatedCubeMeshData->indices.size(), nullptr);
	if (pGeneratedBoxMesh == nullptr) {
		print("Unable to load mesh");
	}
	ArcAssets::m_meshVector.push_back(std::move(pGeneratedBoxMesh));

	DX11Engine::MaterialInitStruct misTriangle = DX11Engine::MaterialInitStruct();
	std::string shaderPath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "SimpleShader.fx";
	FL(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath, "VS_Main", "vs_4_0", &(misTriangle.m_vertexShaderBuffer), &(misTriangle.m_vertexShader)));
	FL(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::SolidColorLayout, ARRAYSIZE(DX11Engine::SolidColorLayout), &(misTriangle.m_vertexShaderBuffer), &(misTriangle.m_inputLayout)));
	FL(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath, "PS_Main", "ps_4_0", &(misTriangle.m_pixelShaderBuffer), &(misTriangle.m_pixelShader)));
	std::shared_ptr<DX11Engine::ArcMaterial> simpleMaterial = std::make_shared<DX11Engine::ArcMaterial>("SimpleMaterial", misTriangle.m_vertexShader, misTriangle.m_pixelShader, misTriangle.m_inputLayout, nullptr, nullptr);
	ArcAssets::m_materialVector.push_back(std::move(simpleMaterial));

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

	//五彩正方形材质
	DX11Engine::MaterialInitStruct misSimpleBox = DX11Engine::MaterialInitStruct();
	std::string shaderPath2 = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "TestBoxShader.fx";
	FL(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath2, "VS", "vs_4_0", &(misSimpleBox.m_vertexShaderBuffer), &(misSimpleBox.m_vertexShader)));
	FL(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::TestBoxLayout, ARRAYSIZE(DX11Engine::TestBoxLayout), &(misSimpleBox.m_vertexShaderBuffer), &(misSimpleBox.m_inputLayout)));
	FL(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath2, "PS", "ps_4_0", &(misSimpleBox.m_pixelShaderBuffer), &(misSimpleBox.m_pixelShader)));

	ID3D11Buffer* tempConstantBuffer = NULL;
	FL(DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescMVP, &tempConstantBuffer));

	ID3D11Buffer* lightConstantBuffer = NULL;
	FL(DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescLight, &lightConstantBuffer));

	std::shared_ptr<DX11Engine::ArcMaterial> TestBoxMaterial = std::make_shared<DX11Engine::ArcMaterial>("TestBoxMaterial", misSimpleBox.m_vertexShader, misSimpleBox.m_pixelShader, misSimpleBox.m_inputLayout, tempConstantBuffer, lightConstantBuffer);
	ArcAssets::m_materialVector.push_back(std::move(TestBoxMaterial));

	//带贴图光照正方形材质
	DX11Engine::MaterialInitStruct misStandardMat = DX11Engine::MaterialInitStruct();
	std::string shaderPath3 = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "StandardShader.fx";
	FL(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath3, "VS", "vs_4_0", &(misStandardMat.m_vertexShaderBuffer), &(misStandardMat.m_vertexShader)));
	FL(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::VertextNormalTangentTexcoordLayout, ARRAYSIZE(DX11Engine::VertextNormalTangentTexcoordLayout), &(misStandardMat.m_vertexShaderBuffer), &(misStandardMat.m_inputLayout)));
	FL(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath3, "PS", "ps_4_0", &(misStandardMat.m_pixelShaderBuffer), &(misStandardMat.m_pixelShader)));
	
	ID3D11Buffer* tempConstantBuffer3 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescMVP, &tempConstantBuffer3);

	ID3D11Buffer* lightConstantBuffer3 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescLight, &lightConstantBuffer3);

	std::shared_ptr<DX11Engine::ArcMaterial> StandardMaterial = std::make_shared<DX11Engine::ArcMaterial>("StandardMaterial", misStandardMat.m_vertexShader, misStandardMat.m_pixelShader, misStandardMat.m_inputLayout, tempConstantBuffer3, lightConstantBuffer3);
	ArcAssets::m_materialVector.push_back(std::move(StandardMaterial));
/**/
	//深度贴图材质
	DX11Engine::MaterialInitStruct misDepthMat = DX11Engine::MaterialInitStruct();
	std::string shaderPath4 = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "DepthShader.fx";
	FL(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPath4, "VS", "vs_4_0", &(misDepthMat.m_vertexShaderBuffer), &(misDepthMat.m_vertexShader)));
	FL(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::VertextNormalTangentTexcoordLayout, ARRAYSIZE(DX11Engine::VertextNormalTangentTexcoordLayout), &(misDepthMat.m_vertexShaderBuffer), &(misDepthMat.m_inputLayout)));
	FL(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPath4, "PS", "ps_4_0", &(misDepthMat.m_pixelShaderBuffer), &(misDepthMat.m_pixelShader)));

	ID3D11Buffer* tempConstantBuffer4 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescMVP, &tempConstantBuffer4);

	ID3D11Buffer* lightConstantBuffer4 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescLight, &lightConstantBuffer4);

	std::shared_ptr<DX11Engine::ArcMaterial> DepthMaterial = std::make_shared<DX11Engine::ArcMaterial>("DepthMaterial", misDepthMat.m_vertexShader, misDepthMat.m_pixelShader, misDepthMat.m_inputLayout, tempConstantBuffer4, lightConstantBuffer4);
	ArcAssets::m_materialVector.push_back(std::move(DepthMaterial));

	/*//猫材质
	DX11Engine::MaterialInitStruct misCatMat = DX11Engine::MaterialInitStruct();
	std::string shaderPathCat = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "StandardShader.fx";
	FL(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPathCat, "VS", "vs_4_0", &(misCatMat.m_vertexShaderBuffer), &(misCatMat.m_vertexShader)));
	//FL(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::VertextNormalTangentTexcoordLayout, ARRAYSIZE(DX11Engine::VertextNormalTangentTexcoordLayout), &(misCatMat.m_vertexShaderBuffer), &(misStandardMat.m_inputLayout)));
	//print(pCatMesh->m_pInputLayout);
	misCatMat.m_inputLayout = pCatMesh->m_pInputLayout;
	FL(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPathCat, "PS", "ps_4_0", &(misCatMat.m_pixelShaderBuffer), &(misCatMat.m_pixelShader)));

	ID3D11Buffer* tempConstantBufferCat = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescMVP, &tempConstantBufferCat);

	ID3D11Buffer* lightConstantBufferCat = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescLight, &lightConstantBufferCat);

	std::shared_ptr<DX11Engine::ArcMaterial> CatMaterial = std::make_shared<DX11Engine::ArcMaterial>("CatMaterial", misCatMat.m_vertexShader, misCatMat.m_pixelShader, misCatMat.m_inputLayout, tempConstantBufferCat, lightConstantBufferCat);
	ArcAssets::m_materialVector.push_back(std::move(CatMaterial));*/

	//盒子贴图
	std::string texturePath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::TEXTURE_PATH + "WoodCrate.dds";
	auto boxTexture = DX11Engine::ArcAssetLoader::LoadTexture("BoxTexture", texturePath);

	//天空盒贴图
	std::string skyBoxTexturePath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::TEXTURE_PATH + "desertcube1024.dds";
	auto skyBoxTexture = DX11Engine::ArcAssetLoader::LoadTexture("SkyBoxTexture", skyBoxTexturePath);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MaxAnisotropy = 4;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DX11Engine::ArcAssetLoader::SetTexture(&sampDesc, boxTexture, 0, 0);
	DX11Engine::ArcAssetLoader::SetTexture(&sampDesc, skyBoxTexture, 1, 0);

	//天空盒
	DX11Engine::MaterialInitStruct misSkyBoxMat = DX11Engine::MaterialInitStruct();
	std::string shaderPathSkyBox = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::SHADER_PATH + "SkyBoxShader.fx";
	FL(DX11Engine::ArcAssetLoader::LoadVertexShader(shaderPathSkyBox, "VS", "vs_4_0", &(misSkyBoxMat.m_vertexShaderBuffer), &(misSkyBoxMat.m_vertexShader)));
	FL(DX11Engine::ArcAssetLoader::ConfigInputLayout(DX11Engine::VertextNormalTangentTexcoordLayout, ARRAYSIZE(DX11Engine::VertextNormalTangentTexcoordLayout), &(misSkyBoxMat.m_vertexShaderBuffer), &(misSkyBoxMat.m_inputLayout)));
	FL(DX11Engine::ArcAssetLoader::LoadPixelShader(shaderPathSkyBox, "PS", "ps_4_0", &(misSkyBoxMat.m_pixelShaderBuffer), &(misSkyBoxMat.m_pixelShader)));

	ID3D11Buffer* tempConstantBuffer6 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescMVP, &tempConstantBuffer6);

	ID3D11Buffer* lightConstantBuffer6 = NULL;
	DX11Engine::ArcAssetLoader::CreateConstantBuffer(DX11Engine::ArcRHI::g_pd3dDevice, &cbDescLight, &lightConstantBuffer6);

	std::shared_ptr<DX11Engine::ArcMaterial> skyBoxMaterial = std::make_shared<DX11Engine::ArcMaterial>("SkyBoxMaterial", misSkyBoxMat.m_vertexShader, misSkyBoxMat.m_pixelShader, misSkyBoxMat.m_inputLayout, tempConstantBuffer6, lightConstantBuffer6);
	ArcAssets::m_materialVector.push_back(std::move(skyBoxMaterial));

	return true;
}
