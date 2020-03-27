#pragma once

#include "CommonHeaders.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"
#include "ArcTransform.h"
#include "ArcPrespCamera.h"
#include "ArcMath.h"
#include "Light.h"

namespace DX11Engine {

	struct layoutStruct {
	public:
		layoutStruct(int index, int size, int totalLength, int phase, int dataSize);
		int m_index;
		int m_width;
		int m_totalLength;
		int m_phase;
		int m_dataSize;
	};

	class ArcRenderer
	{
	public:
		ArcRenderer() = default;
		ArcRenderer(std::shared_ptr<class ArcMaterial> material, size_t vertexDataSize, float vertexData[], unsigned int texture, const std::vector<layoutStruct>& layoutVector);
		~ArcRenderer() = default;
		static bool Render(std::shared_ptr<ArcMesh> pMesh, std::shared_ptr<ArcMaterial> pMaterial, std::shared_ptr<ArcTransform> pTransform, std::shared_ptr<ArcCameraBase> pCamera, std::shared_ptr<DirectionalLight> pMainLight);
		static bool RenderToDepthForShadow(std::shared_ptr<ArcMesh> pMesh, std::shared_ptr<ArcMaterial> pMaterial, std::shared_ptr<ArcTransform> pTransform, std::shared_ptr<DirectionalLight> pMainLight, int level);

	private:
		
		static bool SetConstantBuffer(ID3D11DeviceContext* immediateContext, ID3D11Buffer* constantBuffer, void* resources, size_t size);
	};

}

