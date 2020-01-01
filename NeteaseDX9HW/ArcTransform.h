#pragma once

#include "CommonHeaders.h"
#include "ArcMath.h"

namespace DX11Engine { //跨平台无关

	class ArcTransform
	{
	public:
		ArcTransform();
		~ArcTransform() = default;
		const float3 position() const;
		const float3 scale() const;
		const float3 rotation() const; //欧拉角
		const quaternion quaternion() const;
		const mat4 positionMatrix() const;
		const mat4 rotationMatrix() const;
		const mat4 scaleMatrix() const;
		const mat4 transformMatrix() const;
		void setPosition(float3 position);
		void setScale(float3 scale);
		void setRotation(float3 rotation);
		void translate(float3 offset);
		void rotate(float3 eularAngle);
		void rotate(float rightAngle, float upAngle, float forwardAngle);
		void lookAt(float3 target);

		float3 forward() const; //Vector3(0, 0, 1)
		float3 right() const; //Vector3(1, 0, 0)
		float3 up() const; //Vector3(0, 1, 0)
	private:
		float3 m_position;
		float3 m_scale;
		float3 m_rotation;

		void normalizeRotation();
	};

}

