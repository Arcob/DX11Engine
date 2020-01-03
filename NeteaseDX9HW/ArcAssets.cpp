#include "ArcAssets.h"

namespace DX11Engine {

	ArcAssets::ArcAssets() {}

	bool ArcAssets::Load() {
		print("Load Base Class ArcAssets");

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