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
			float4 tempVec = float4(LocalPosition().x, LocalPosition().y, LocalPosition().z, 1);
			float4 tempResult = MatrixMultVector(m_parent->ScaleMatrix() * m_parent->RotationMatrix(), tempVec);
			return float3(tempResult.x, tempResult.y, tempResult.z);
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
		return QuaternionTORotation(m_rotation);
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
		normalizeRotation();
	}

	void ArcTransform::Translate(float3 offset) {
		m_position = float3(m_position.x + offset.x, m_position.y + offset.y, m_position.y + offset.y);
	}

	void ArcTransform::Rotate(float3 eularAngle) {
		Rotate(eularAngle.x, eularAngle.y, eularAngle.z);
	}

	void ArcTransform::LookAt(float3 target) {  // 这个lookat的Up
		if (NearlyEquals(target, m_position)) {
			return;
		}
		float3 direction = NormalizeFloat3(float3(target.x - m_position.x, target.y - m_position.y, target.z - m_position.z));
		float angleX = DegreeToRadians(asinf(-direction.y));
		float angleY = -DegreeToRadians(atan2f(-direction.x, -direction.z));
		normalizeRotation();
	}

	void ArcTransform::Rotate(float rightAngle, float upAngle, float forwardAngle) {
		m_rotation = float3(m_rotation.x + rightAngle, m_rotation.y + upAngle, m_rotation.z + forwardAngle);
		normalizeRotation();
	}

	float3 ArcTransform::Forward() const {
		float4 forward = MatrixMultVector(Inverse(ArcTransform::RotationMatrix()), float4(0, 0, -1, 1));
		return float3(forward.x, forward.y, forward.z);
	}

	float3 ArcTransform::Right() const {
		float4 right = MatrixMultVector(Inverse(ArcTransform::RotationMatrix()), float4(1, 0, 0, 1));
		return float3(right.x, right.y, right.z);
	}

	float3 ArcTransform::Up() const {
		float4 up = MatrixMultVector(Inverse(ArcTransform::RotationMatrix()), float4(0, 1, 0, 1));
		return float3(up.x, up.y, up.z);
	}

	void ArcTransform::normalizeRotation() {
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