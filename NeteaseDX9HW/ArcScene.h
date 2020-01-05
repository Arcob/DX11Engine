#pragma once

#include "CommonHeaders.h"

namespace DX11Engine {
	class ArcGameObject;
	class Light;

	class ArcScene
	{
	public:
		ArcScene(std::string m_name);
		ArcScene(std::string m_name, std::shared_ptr<Light> mainLight);
		~ArcScene() = default;
		void AddGameObject(std::shared_ptr<ArcGameObject> gameObject);
		std::vector<std::shared_ptr<ArcGameObject>>& GetGameObjectsInScene();
		void SetMainLight(std::shared_ptr<Light> light);
		const std::shared_ptr<Light> GetMainLight() const;
		void AddSecondaryLight(std::shared_ptr<Light> light);
		std::vector<std::shared_ptr<Light>>& GetSecondaryLights();

	private:
		std::string m_name;
		std::vector<std::shared_ptr<ArcGameObject>> m_sceneGameObjects;
		std::shared_ptr<Light> m_mainLight;
		std::vector <std::shared_ptr<Light>> m_secondaryLights;
	};
}



