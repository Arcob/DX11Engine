#include "ArcAssets.h"
#include "DriverSetting.h"
#include "SimpleVertexs.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"
#include "ArcAssetLoader.h"

namespace DX11Engine {

	ArcAssets::ArcAssets() {}

	bool ArcAssets::Load() { //加载一些通用的资源
		if (ENABLE_SHADOW) {
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

			//深度贴图材质,阴影要用,应该改成工具材质
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
		}
		
		return true;
	}


	std::shared_ptr<DX11Engine::ArcMesh> ArcAssets::findMesh(std::string name) {
		for (int i = 0; i < m_meshVector.size(); i++) {
			if (m_meshVector[i]->m_meshName == name) {
				return m_meshVector[i];
			}
		}
		return nullptr;
	}

	std::shared_ptr<DX11Engine::ArcMaterial> ArcAssets::findMaterial(std::string name) {
		for (int i = 0; i < m_materialVector.size(); i++) {
			if (m_materialVector[i]->m_name == name) {
				return m_materialVector[i];
			}
		}
		return nullptr;
	}

}