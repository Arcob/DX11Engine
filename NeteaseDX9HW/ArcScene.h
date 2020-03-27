#pragma once

#include "CommonHeaders.h"

namespace DX11Engine {
	class ArcGameObject;
	class ArcCameraBase;
	class DirectionalLight;
	class Light;

	class ArcScene
	{
	public:
		ArcScene(std::string m_name);
		ArcScene(std::string m_name, std::shared_ptr<DirectionalLight> mainLight);
		~ArcScene() = default;
		void AddGameObject(std::shared_ptr<ArcGameObject> gameObject);
		std::vector<std::shared_ptr<ArcGameObject>>& GetGameObjectsInScene();
		void SetMainCamera(std::shared_ptr<ArcCameraBase> mainCamera);
		const std::shared_ptr<ArcCameraBase> GetMainCamera() const;
		void SetMainLight(std::shared_ptr<DirectionalLight> light);
		const std::shared_ptr<DirectionalLight> GetMainLight() const;
		void AddSecondaryLight(std::shared_ptr<Light> light);
		std::vector<std::shared_ptr<Light>>& GetSecondaryLights();

	private:
		std::string m_name;
		std::vector<std::shared_ptr<ArcGameObject>> m_sceneGameObjects;
		std::shared_ptr<ArcCameraBase> m_mainCamera;
		std::shared_ptr<DirectionalLight> m_mainLight;
		std::vector <std::shared_ptr<Light>> m_secondaryLights;
	};
}



