#include "ArcApplication.h"

namespace DX11Engine {
	ArcApplication::ArcApplication(unsigned int WIDTH, unsigned int HEIGHT) : m_width(WIDTH), m_height(HEIGHT) {}

	ArcApplication::ArcApplication(std::string name, std::vector<std::shared_ptr<class ArcScene>> &inputSceneList, int mainSceneIndex, unsigned int WIDTH, unsigned int HEIGHT) :
		m_name(name), m_isRunning(true), m_width(WIDTH), m_height(HEIGHT), m_sceneList(std::move(inputSceneList)), m_mainScene(inputSceneList[mainSceneIndex % inputSceneList.size()])
	{
	}

	std::shared_ptr<class ArcScene> ArcApplication::MainScene() {
		return m_mainScene;
	}

	std::shared_ptr<class ArcScene> ArcApplication::GetScene(int index) {
		if (index > m_sceneList.size()) {
			std::cout << "invalid scene index" << std::endl;
			return nullptr;
		}
		return m_sceneList[index];
	}

	void ArcApplication::LoadScene() {

	}

	const std::string ArcApplication::Name() {
		return m_name;
	}

	void ArcApplication::SetName(std::string name) {
		m_name = name;
	}

	const unsigned int ArcApplication::Width() {
		return m_width;
	}
	const unsigned int ArcApplication::Height() {
		return m_height;
	}

}