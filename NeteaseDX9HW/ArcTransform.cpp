#include "ArcTransform.h"

namespace DX11Engine {
	ArcTransform::ArcTransform() :
		m_position(0.0f, 0.0f, 0.0f),
		m_scale(1.0f, 1.0f, 1.0f),
		m_rotation(0.0f, 0.0f, 0.0f)
	{
	}

	const float3 ArcTransform::position() const {
		return m_position;
	}

	const float3 ArcTransform::scale() const {
		return m_scale;
	}

	const float3 ArcTransform::rotation() const {
		return m_rotation;
	}

	const quaternion ArcTransform::quaternion() const {
		return QuaternionTORotation(m_rotation);
	}

	const mat4 ArcTransform::positionMatrix() const {
		return Vector3ToTranslationMatrix(m_position);
	}

	const mat4 ArcTransform::rotationMatrix() const {
		return EularAngleToRotationMatrix(m_rotation);
	}

	const mat4 ArcTransform::scaleMatrix() const {
		return Vector3ToScaleMatrix(m_scale);
	}

	const mat4 ArcTransform::transformMatrix() const {
		return scaleMatrix() * rotationMatrix() * positionMatrix();//DX的mvp要和Opengl反着乘
	}

	void ArcTransform::setPosition(float3 position) {
		m_position = position;
	}

	void ArcTransform::setScale(float3 scale) {
		m_scale = scale;
	}

	void ArcTransform::setRotation(float3 rotation) {
		m_rotation = rotation;
	}

	void ArcTransform::translate(float3 offset) {
		m_position = float3(m_position.x + offset.x, m_position.y + offset.y, m_position.y + offset.y);
	}

	void ArcTransform::rotate(float3 eularAngle) {
		rotate(eularAngle.x, eularAngle.y, eularAngle.z);
	}

	void ArcTransform::lookAt(float3 target) {  // 这个lookat的Up
		if (NearlyEquals(target, m_position)) {
			return;
		}
		float3 direction = NormalizeFloat3(float3(target.x - m_position.x, target.y - m_position.y, target.z - m_position.z));
		float angleX = DegreeToRadians(asinf(-direction.y));
		float angleY = -DegreeToRadians(atan2f(-direction.x, -direction.z));
		normalizeRotation();
	}

	void ArcTransform::rotate(float rightAngle, float upAngle, float forwardAngle) {
		m_rotation = float3(m_rotation.x + rightAngle, m_rotation.y + upAngle, m_rotation.z + forwardAngle);
		normalizeRotation();
	}

	float3 ArcTransform::forward() const {
		float4 forward = MatrixMultVector(Inverse(ArcTransform::rotationMatrix()), float4(0, 0, -1, 1));
		return float3(forward.x, forward.y, forward.z);
	}

	float3 ArcTransform::right() const {
		float4 right = MatrixMultVector(Inverse(ArcTransform::rotationMatrix()), float4(1, 0, 0, 1));
		return float3(right.x, right.y, right.z);
	}

	float3 ArcTransform::up() const {
		float4 up = MatrixMultVector(Inverse(ArcTransform::rotationMatrix()), float4(0, 1, 0, 1));
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
}