#pragma once

#include "CommonHeaders.h"
#include "ArcMesh.h"
#include "ArcMaterial.h"

namespace DX11Engine {

	class ArcAssets
	{
	public:
		ArcAssets();
		virtual ~ArcAssets() = default;
		virtual bool Load();
		std::shared_ptr<DX11Engine::ArcMesh> findMesh(std::string name);
		std::shared_ptr<DX11Engine::ArcMaterial> findMaterial(std::string name);

		std::vector<std::shared_ptr<DX11Engine::ArcMesh>> m_meshVector;
		std::vector<std::shared_ptr<DX11Engine::ArcMaterial>> m_materialVector;
	private:
		
		//class ID3D11Device* m_pDevice; //device指针强转过来的
	};

}

