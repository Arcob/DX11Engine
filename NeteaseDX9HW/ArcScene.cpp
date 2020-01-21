#include "ArcScene.h"

namespace DX11Engine {

	ArcScene::ArcScene(std::string name) {
		m_name = name;
		m_mainLight = nullptr;
		m_sceneGameObjects = {};
		m_secondaryLights = {};
	}

	ArcScene::ArcScene(std::string name, std::shared_ptr<DirectionalLight> mainLight) {
		m_name = name;
		m_mainLight = mainLight;
		m_sceneGameObjects = {};
		m_secondaryLights = {};
	}

	void ArcScene::AddGameObject(std::shared_ptr<ArcGameObject> gameObject) {
		m_sceneGameObjects.push_back(gameObject);
	}

	std::vector<std::shared_ptr<ArcGameObject>>& ArcScene::GetGameObjectsInScene() {
		return m_sceneGameObjects;
	}

	void ArcScene::SetMainCamera(std::shared_ptr<ArcCamera> mainCamera) {
		m_mainCamera = mainCamera;
	}

	const std::shared_ptr<ArcCamera> ArcScene::GetMainCamera() const {
		return m_mainCamera;
	}

	void ArcScene::SetMainLight(std::shared_ptr<DirectionalLight> light) {
		m_mainLight = light;
	}

	const std::shared_ptr<DirectionalLight> ArcScene::GetMainLight() const {
		return m_mainLight;
	}

	void ArcScene::AddSecondaryLight(std::shared_ptr<Light> light) {
		m_secondaryLights.push_back(light);
	}

	std::vector<std::shared_ptr<Light>>& ArcScene::GetSecondaryLights() {
		return m_secondaryLights;
	}
}