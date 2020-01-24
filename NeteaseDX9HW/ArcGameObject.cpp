#include "ArcGameObject.h"
#include "ArcBehaviour.h"

namespace DX11Engine {
	ArcGameObject::ArcGameObject(std::string name)
	{
		m_name = name;
	}


	std::list<ArcGameObject>* ArcGameObject::m_gameObjectList = nullptr;
	std::vector<std::shared_ptr<ArcGameObject>> ArcGameObject::m_gameObjectVector = std::vector<std::shared_ptr<ArcGameObject>>();

	void ArcGameObject::AttachScript(std::shared_ptr<ArcBehaviour> script) {
		ArcBehaviourList.push_back(script);
		//std::cout << " a: " << this->behaviourListLength() << std::endl;
		script->SetGameObject(std::make_shared<ArcGameObject>(*this));
		//std::cout << " b: " << script->gameObject()->behaviourListLength() << std::endl;
	}

	const int ArcGameObject::BehaviourListLength() const {
		return ArcBehaviourList.size();
	}

	const std::vector<std::shared_ptr<ArcBehaviour>> ArcGameObject::GetBehaviourList() const {
		return ArcBehaviourList;
	}

	/*const ArcTransform ArcGameObject::Transform() const {
		return m_transform;
	}*/

	std::shared_ptr<ArcTransform> const ArcGameObject::TransformPtr() {
		return m_transform;
	}

	void ArcGameObject::SetTransfrom(std::shared_ptr<ArcTransform> transform) {
		m_transform = transform;
	}

	void ArcGameObject::SetName(const std::string& name) {
		m_name = name;
	}

	const std::string ArcGameObject::name() const {
		return m_name;
	}

	void ArcGameObject::SetMesh(std::shared_ptr<ArcMesh> renderer) {
		m_mesh = renderer;
	}

	const std::shared_ptr<ArcMesh> ArcGameObject::Mesh() const {
		return m_mesh;
	}

	void ArcGameObject::SetGameObjectList(std::list<ArcGameObject>* list) {
		m_gameObjectList = list;
	}

	void ArcGameObject::SetGameObjectVector(std::vector<std::shared_ptr<ArcGameObject>> vector) {
		m_gameObjectVector = vector;
	}

	void ArcGameObject::SetMaterial(std::shared_ptr<ArcMaterial> material) {
		m_material = material;
	}

	const std::shared_ptr<ArcMaterial> ArcGameObject::Material() const {
		return m_material;
	}

	void ArcGameObject::RegisterGameObject(std::shared_ptr<ArcGameObject> pGameObject) {
		m_gameObjectVector.push_back(pGameObject);
	}

	std::shared_ptr<ArcGameObject> ArcGameObject::Find(std::string name) {
		for (auto pGameObject : m_gameObjectVector) {
			if (pGameObject->name() == name) {
				return pGameObject;
			}
		}
		return nullptr;
	}

}