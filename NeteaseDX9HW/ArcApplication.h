#pragma once

#include "CommonHeaders.h"

namespace DX11Engine{

class ArcApplication //��ƽ̨�޹أ�׼����Ӷೡ������
{
	public:
		ArcApplication(unsigned int WIDTH, unsigned int HEIGHT);
		ArcApplication(std::string name, std::vector<std::shared_ptr<class ArcScene>> &inputSceneList, int mainSceneIndex, unsigned int WIDTH, unsigned int HEIGHT);
		virtual ~ArcApplication() = default;
		std::shared_ptr<class ArcScene> MainScene();
		std::shared_ptr<class ArcScene> GetScene(int index);
		const std::string Name();
		void SetName(std::string name);
		const unsigned int Width();
		const unsigned int Height();
		virtual void LoadScene();
		void SwitchScene(int targetSceneIndex); //��ʵ��

	private:
		unsigned int m_width = 800;
		unsigned int m_height = 600;
		std::string m_name;
		bool m_isRunning = true;

	protected:
		std::shared_ptr<class ArcScene> m_mainScene;
		std::vector<std::shared_ptr<class ArcScene>> m_sceneList;
};

};

