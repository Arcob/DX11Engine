#pragma once

#include "CommonHeaders.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"
#include "ArcTransform.h"
#include "ArcCamera.h"

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
		static bool Render(std::shared_ptr<ArcMesh> pMesh, std::shared_ptr<ArcMaterial> pMaterial, std::shared_ptr<ArcTransform> pTransform, std::shared_ptr<ArcCamera> pCamera);
	private:

	};

}

