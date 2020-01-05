#include "ArcScene.h"

namespace DX11Engine {

	ArcScene::ArcScene(std::string name) {
		m_name = name;
		m_mainLight = nullptr;
		m_sceneGameObjects = {};
		m_secondaryLights = {};
	}

	ArcScene::ArcScene(std::string name, std::shared_ptr<Light> mainLight) {
		m_name = name;
		m_mainLight = mainLight;
		m_sceneGameObjects = {};
		m_secondaryLights = {};
	}

	void ArcScene::AddGameObject(std::shared_ptr<ArcGameObject> gameObject) {
		//print(m_sceneGameObjects);
		m_sceneGameObjects.push_back(gameObject);
	}

	std::vector<std::shared_ptr<ArcGameObject>>& ArcScene::GetGameObjectsInScene() {
		return m_sceneGameObjects;
	}

	void ArcScene::SetMainLight(std::shared_ptr<Light> light) {
		m_mainLight = light;
	}

	const std::shared_ptr<Light> ArcScene::GetMainLight() const {
		return m_mainLight;
	}

	void ArcScene::AddSecondaryLight(std::shared_ptr<Light> light) {
		m_secondaryLights.push_back(light);
	}

	std::vector<std::shared_ptr<Light>>& ArcScene::GetSecondaryLights() {
		return m_secondaryLights;
	}
}