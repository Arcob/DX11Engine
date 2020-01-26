#include "ArcTransform.h"

namespace DX11Engine {
	ArcTransform::ArcTransform() :
		m_position(0.0f, 0.0f, 0.0f),
		m_scale(1.0f, 1.0f, 1.0f),
		m_rotation(0.0f, 0.0f, 0.0f)
	{
		m_children = {};
		m_parent = nullptr;
	}

	const float3 ArcTransform::Position() const {
		if (m_parent != nullptr) {
			float4 tempVec = float4(LocalPosition().x, LocalPosition().y, LocalPosition().z, 1);
			float4 tempResult = MatrixMultVector(m_parent->ScaleMatrix() * m_parent->RotationMatrix() * m_parent->PositionMatrix(), tempVec);
			return float3(tempResult.x, tempResult.y, tempResult.z);
		}
		return LocalPosition();
	}

	const float3 ArcTransform::LocalPosition() const {
		return m_position;
	}

	const float3 ArcTransform::Rotation() const {
		if (m_parent != nullptr) {
			/*float4 tempVec = float4(LocalRotation().x, LocalRotation().y, LocalRotation().z, 1);
			
			//PrintMat(m_parent->RotationMatrix());
			//PrintFloat4(MatrixMultVector(m_parent->ScaleMatrix() * m_parent->RotationMatrix(), tempVec));
			//PrintFloat4(MatrixMultVector(m_parent->RotationMatrix(), tempVec));
			float4 tempResult = MatrixMultVector(m_parent->ScaleMatrix() * m_parent->RotationMatrix(), tempVec);
			return float3(tempResult.x, tempResult.y, tempResult.z);*/
			float3 parentRotation = m_parent->Rotation();
			return normalizeRotation(float3(parentRotation.x + m_rotation.x, parentRotation.y + m_rotation.y, parentRotation.z + m_rotation.z));
		}
		return LocalRotation();
	}

	const float3 ArcTransform::LocalRotation() const {
		return m_rotation;
	}

	const float3 ArcTransform::Scale() const {
		if (m_parent != nullptr) {
			float4 tempVec = float4(LocalScale().x, LocalScale().y, LocalScale().z, 1);
			float4 tempResult = MatrixMultVector(m_parent->ScaleMatrix(), tempVec);
			return float3(tempResult.x, tempResult.y, tempResult.z);
		}
		return LocalScale();
	}

	const float3 ArcTransform::LocalScale() const {
		return m_scale;
	}

	const quaternion ArcTransform::Quaternion() const {
		return RotationTOQuaternion(m_rotation);
	}

	const mat4 ArcTransform::PositionMatrix() const {
		return Vector3ToTranslationMatrix(Position());
	}

	const mat4 ArcTransform::RotationMatrix() const {
		return EularAngleToRotationMatrix(Rotation());
	}

	const mat4 ArcTransform::ScaleMatrix() const {
		return Vector3ToScaleMatrix(Scale());
	}

	const mat4 ArcTransform::TransformMatrix() const {
		return ScaleMatrix() * RotationMatrix() * PositionMatrix();//DX的mvp要和Opengl反着乘
	}

	void ArcTransform::SetLocalPosition(float3 position) {
		m_position = position;
	}

	void ArcTransform::SetLocalScale(float3 scale) {
		m_scale = scale;
	}

	void ArcTransform::SetLocalRotation(float3 rotation) {
		m_rotation = rotation;
		normalizeLocalRotation();
	}

	void ArcTransform::Translate(float3 offset) {
		m_position = float3(m_position.x + offset.x, m_position.y + offset.y, m_position.z + offset.z);
	}

	void ArcTransform::Rotate(float3 eularAngle) {
		Rotate(eularAngle.x, eularAngle.y, eularAngle.z);
	}

	void ArcTransform::LookAt(float3 target) {  // 这个lookat的Up
		if (NearlyEquals(target, Position())) {
			return;
		}
		float3 pos = Position();
		float3 direction = NormalizeFloat3(float3(target.x - pos.x, target.y - pos.y, target.z - pos.z));
		float angleX = DegreeToRadians(asinf(-direction.y));
		float angleY = -DegreeToRadians(atan2f(-direction.x, -direction.z));
		normalizeLocalRotation();
	}

	void ArcTransform::Rotate(float rightAngle, float upAngle, float forwardAngle) {
		m_rotation = float3(m_rotation.x + rightAngle, m_rotation.y + upAngle, m_rotation.z + forwardAngle);
		normalizeLocalRotation();
	}

	float3 ArcTransform::Forward() const {
		return TransformCoord(Float3Forward(), RotationMatrix());
	}

	float3 ArcTransform::Right() const {
		return TransformCoord(Float3Right(), RotationMatrix());
	}

	float3 ArcTransform::Up() const {
		return TransformCoord(Float3Up(), RotationMatrix());
	}

	void ArcTransform::normalizeLocalRotation() {
		float angleX = m_rotation.x;
		float angleY = m_rotation.y;
		float angleZ = m_rotation.z;

		angleX = fmodf(angleX, 360.0f); //fmodf可能返回负数，所以之后还得加360.。。
		angleY = fmodf(angleY, 360.0f);
		angleZ = fmodf(angleZ, 360.0f);

		if (angleX < 0.0f)
			angleX += 360.0f;
		if (angleY < 0.0f)
			angleY += 360.0f;
		if (angleZ < 0.0f)
			angleZ += 360.0f;

		m_rotation = float3(angleX, angleY, angleZ);
	}

	void ArcTransform::SetParent(std::shared_ptr<ArcTransform> self, std::shared_ptr<ArcTransform> parent) {
		self->m_parent = parent;
		if (std::find((parent->m_children).cbegin(), (parent->m_children).cend(), self) == (parent->m_children).cend()) {
			(parent->m_children).push_back(self);
		}
	}
}