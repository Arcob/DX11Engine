#pragma once

#include "CommonHeaders.h"
#include <DirectXMath.h>

namespace DX11Engine {

	const float JUDGE_EQUAL_BIAS = 0.0001f;
	const float PI = 3.1415926f;
	const float ONE_DIVIDE_PI = 0.318309891613572f;
	const float DEGREE_TO_RADIANS = 0.0174532925f;//1¡ã=0.0174532925 »¡¶È
	const float RADIAN_TO_DEGREE = 57.29578049f;

	typedef DirectX::XMFLOAT4 float4;
	typedef DirectX::XMFLOAT3 float3;
	typedef DirectX::XMFLOAT2 float2;
	typedef DirectX::FXMVECTOR quaternion;
	typedef DirectX::XMMATRIX mat4;

	inline quaternion QuaternionTORotation(float3 rotation) {
		return DirectX::XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	}

	inline mat4 Vector3ToTranslationMatrix(float3 position) {
		return DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}

	inline mat4 Vector3ToScaleMatrix(float3 scale) {
		return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	}

	inline mat4 EularAngleToRotationMatrix(float3 eularAngle) {
		return DirectX::XMMatrixRotationRollPitchYaw(eularAngle.x, eularAngle.y, eularAngle.z);
	}

	inline mat4 QuaternionToRotationMatrix(quaternion quat) {
		return DirectX::XMMatrixRotationQuaternion(quat);
	}

	inline bool NearlyEquals(float3 a, float3 b) {
		if (abs(a.x-b.x)< JUDGE_EQUAL_BIAS && abs(a.y - b.y) < JUDGE_EQUAL_BIAS && abs(a.z - b.z) < JUDGE_EQUAL_BIAS) {
			return true;
		}
		return false;
	}

	inline float3 NormalizeFloat3(float3 a) {
		float total = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
		return float3(a.x/total, a.y / total, a.z / total);
	}

	inline float DegreeToRadians(float degree) {
		return degree * DEGREE_TO_RADIANS;
	}

	inline mat4 Inverse(mat4 matrix){
		return DirectX::XMMatrixInverse(nullptr, matrix);
	}

	inline float4 MatrixMultVector(mat4 matrix, float4 vector) {
		float4 result;
		DirectX::XMStoreFloat4(&result, DirectX::XMVector4Transform(XMLoadFloat4(&vector), matrix));
		return result;
	}
}

