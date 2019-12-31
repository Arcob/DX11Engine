#pragma once
#include "CommonHeaders.h"

namespace DX11Engine {
	class ArcGameObject;

	class ArcBehaviour
	{
	public:
		ArcBehaviour() = default;
		virtual ~ArcBehaviour() = default;
		virtual void Awake();
		virtual void Start();
		virtual void Update();
		std::shared_ptr<ArcGameObject> const gameObject() const;
		void setGameObject(std::shared_ptr<ArcGameObject> gameObject);

	private:
		std::shared_ptr<ArcGameObject> _gameObject = nullptr;

	};
}

