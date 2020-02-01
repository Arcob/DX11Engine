#pragma once

#include "CommonHeaders.h"
#include "ArcMath.h"

namespace DX11Engine { //跨平台无关

	class ArcTransform
	{
	public:
		ArcTransform();
		~ArcTransform() = default;
		const float3 Position() const;
		const float3 LocalPosition() const;
		const float3 Rotation() const; //欧拉角
		const float3 LocalRotation() const; //欧拉角
		const float3 Scale() const;
		const float3 LocalScale() const;
		const quaternion Quaternion() const;
		const mat4 PositionMatrix() const;
		const mat4 RotationMatrix() const;
		const mat4 ScaleMatrix() const;
		const mat4 TransformMatrix() const;
		void SetLocalPosition(float3 position);
		void SetLocalRotation(float3 rotation);
		void SetLocalScale(float3 scale);	
		void SetPosition(float3 position);
		void SetRotation(float3 rotation);
		void SetScale(float3 scale);
		float3 GetParentsScales();
		void Translate(float3 offset);
		void Rotate(float3 eularAngle);
		void Rotate(float rightAngle, float upAngle, float forwardAngle);
		void LookAt(float3 target);
		void RotateAround(float3 pos, float3 vec, float angle);
		
		float3 Forward() const; //Vector3(0, 0, 1)
		float3 Right() const; //Vector3(1, 0, 0)
		float3 Up() const; //Vector3(0, 1, 0)

		static void SetParent(std::shared_ptr<ArcTransform> self, std::shared_ptr<ArcTransform> parent);

		std::vector<std::shared_ptr<ArcTransform>> m_children;
		std::shared_ptr<ArcTransform> m_parent;
	private:
		float3 m_position;
		float3 m_scale;
		float3 m_rotation;
		
		void normalizeLocalRotation();
		
	};

}

