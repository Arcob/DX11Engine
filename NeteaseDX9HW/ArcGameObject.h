#pragma once

#include "CommonHeaders.h"

namespace DX11Engine {

	class ArcBehaviour;
	class ArcTransform;
	class ArcMesh;
	class ArcMaterial;
	class Camera;

	class ArcGameObject
	{
	public:
		ArcGameObject() = default;
		~ArcGameObject() = default;

		void AttachScript(std::shared_ptr<ArcBehaviour> script);
		const int BehaviourListLength() const;
		const std::vector<std::shared_ptr<ArcBehaviour>> GetBehaviourList() const;
		//const ArcTransform Transform() const;//∑µªÿ“˝”√
		std::shared_ptr<ArcTransform> const TransformPtr();
		void SetTransfrom(std::shared_ptr<ArcTransform> transfrom);
		void SetName(const std::string& name);
		const std::string name() const;
		void SetMesh(std::shared_ptr<ArcMesh> mesh);
		const std::shared_ptr<ArcMesh> Mesh() const;
		void SetMaterial(std::shared_ptr<ArcMesh> material);
		const std::shared_ptr<ArcMesh> Material() const;

		template<typename T>
		T* getComponent() {
			for (int i = 0; i < ArcBehaviourList.size(); i++) {
				auto temp = dynamic_cast<T*>(ArcBehaviourList[i].get());
				if (temp != nullptr) {
					return temp;
				}
			}
			return nullptr;
		}

		static void SetGameObjectList(std::list<ArcGameObject>* list);

		static void SetGameObjectVector(std::vector<std::shared_ptr<ArcGameObject>> vector);

		template<typename T>
		static std::vector<std::shared_ptr<ArcGameObject>> findGameObjectsOfType() {
			std::vector<std::shared_ptr<ArcGameObject>> result;// = std::vector<std::shared_ptr<Arc_Engine::ArcGameObject>>();
			//std::list<Arc_Engine::ArcGameObject>::iterator it;//start
			//std::cout << _gameObjectList->size() << std::endl;
			for (int i = 0; i < _gameObjectVector.size(); i++) {
				for (int j = 0; j < (_gameObjectVector[i]->behaviourListLength()); j++) {
					//(it->getBehaviourList())[i]->Start();
					//if (dynamic_cast<T*>(&*((it->getBehaviourList())[i])) != nullptr) {
					if (dynamic_cast<T*>(((_gameObjectVector[i]->getBehaviourList())[j]).get()) != nullptr) {
						//Arc_Engine::ArcGameObject* temp = _gameObjectVector[i];
						result.push_back(_gameObjectVector[i]);
					}
				}
			}
			return result;
		}

	private:
		static std::list<ArcGameObject>* m_gameObjectList;
		static std::vector<std::shared_ptr<ArcGameObject>> m_gameObjectVector;
		std::vector<std::shared_ptr<ArcBehaviour>> ArcBehaviourList;
		std::shared_ptr<ArcTransform> m_transform;
		std::shared_ptr<ArcMesh> m_mesh = nullptr;
		std::shared_ptr<ArcMesh> m_material = nullptr;
		std::string m_name = "EmptyGameObject";
	};

}

