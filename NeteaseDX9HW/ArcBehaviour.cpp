#include "ArcBehaviour.h"

namespace DX11Engine {

	/*ArcBehaviour::ArcBehaviour()
	{
	}


	ArcBehaviour::~ArcBehaviour()
	{
	}*/

	std::shared_ptr<ArcGameObject> const ArcBehaviour::GameObject() const {
		return m_gameObject;
	}

	void ArcBehaviour::Awake()
	{

	}

	void ArcBehaviour::Start()
	{

	}

	void ArcBehaviour::Update()
	{

	}

	void ArcBehaviour::SetGameObject(std::shared_ptr<ArcGameObject> gameObject) {
		m_gameObject = gameObject;
	}

}