#pragma once

#include "CommonHeaders.h"
#include <algorithm>
#include <DirectXMath.h>

const float JUDGE_EQUAL_BIAS = 0.0001f;
const float PI = 3.1415926f;
const float ONE_DIVIDE_PI = 0.318309891613572f;
const float DEGREE_TO_RADIANS = 0.0174532925f;//1°=0.0174532925 弧度
const float RADIAN_TO_DEGREE = 57.29578049f;

typedef DirectX::XMFLOAT4 float4;
typedef DirectX::XMFLOAT3 float3;
typedef DirectX::XMFLOAT2 float2;
typedef DirectX::FXMVECTOR quaternion;
typedef DirectX::XMMATRIX mat4;
typedef DirectX::XMFLOAT4X4 float4x4;

inline float DegreeToRadians(float degree) {
	return degree * DEGREE_TO_RADIANS;
}

inline float RadiansToDegree(float radians) {
	return radians * 57.29578049f;
}

inline quaternion RotationTOQuaternion(float3 rotation) {
	return DirectX::XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
}

inline mat4 Vector3ToTranslationMatrix(float3 position) {
	return DirectX::XMMatrixTranslation(position.x, position.y, position.z);
}

inline mat4 Vector3ToScaleMatrix(float3 scale) {
	return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
}

inline mat4 EularAngleToRotationMatrix(float3 eularAngle) {
	return DirectX::XMMatrixRotationRollPitchYaw(DegreeToRadians(eularAngle.x), DegreeToRadians(eularAngle.y), DegreeToRadians(eularAngle.z));
	//return DirectX::XMMatrixRotationRollPitchYaw(eularAngle.x, eularAngle.y, eularAngle.z);
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

inline float MagnitureFloat3(float3 a) {
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline float3 NormalizeFloat3(float3 a) {
	float total = MagnitureFloat3(a);
	return float3(a.x/total, a.y / total, a.z / total);
}

inline float3 Float3Cross(float3 a, float3 b) {
	float3 result;
	DirectX::XMStoreFloat3(&result, DirectX::XMVector3Cross(XMLoadFloat3(&a), XMLoadFloat3(&b)));
	return result;
}

inline mat4 Inverse(mat4 matrix){
	return DirectX::XMMatrixInverse(nullptr, matrix);
}

inline float4 MatrixMultVector(mat4 matrix, float4 vector) {
	float4 result;
	DirectX::XMStoreFloat4(&result, DirectX::XMVector4Transform(XMLoadFloat4(&vector), matrix));
	return result;
}

inline mat4 CalculatePerspectiveMatrix(float FovAngleY, float AspectRatio, float NearZ, float FarZ) {
	
	return DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);
}

inline mat4 CalculateOrthographicMatrix(float ViewWidth, float ViewHeight, float NearZ, float FarZ) {
	return DirectX::XMMatrixOrthographicLH(ViewWidth, ViewHeight, NearZ, FarZ);
}

inline mat4 CalculateViewMatrix(float3 EyePosition, float3 FocusPosition, float3 UpDirection) {
	return DirectX::XMMatrixLookAtLH(XMLoadFloat3(&EyePosition), XMLoadFloat3(&FocusPosition), XMLoadFloat3(&UpDirection));
}

inline void PrintMat(mat4 matIn) {
	DirectX::XMFLOAT4X4 mScalFL;
	XMStoreFloat4x4(&mScalFL, matIn);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) 
		{
			// 通过 XMFLOAT4X4 的重载括号操作符引用矩阵元素
			std::cout << '\t' << mScalFL(i, j) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	//print(mScalFL._11);
}

inline void PrintFloat3(float3 in) {
	std::cout << in.x << " " << in.y << " " << in.z << " " << std::endl;
}

inline void PrintFloat4(float4 in) {
	std::cout << in.x << " " << in.y << " " << in.z << " " << in.w << " " << std::endl;
}

inline mat4 Transpose(mat4 mat) {
	return XMMatrixTranspose(mat);
}

inline float3 normalizeRotation(float3 rot) {
	float angleX = rot.x;
	float angleY = rot.y;
	float angleZ = rot.z;

	angleX = fmodf(angleX, 360.0f); //fmodf可能返回负数，所以之后还得加360.。。
	angleY = fmodf(angleY, 360.0f);
	angleZ = fmodf(angleZ, 360.0f);

	if (angleX < 0.0f)
		angleX += 360.0f;
	if (angleY < 0.0f)
		angleY += 360.0f;
	if (angleZ < 0.0f)
		angleZ += 360.0f;

	return float3(angleX, angleY, angleZ);
}

inline float3 AddFloat3(float3 a, float3 b) {
	return float3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline float3 Float3Forward() {
	return float3(0.f, 0.f, 1.f);
}

inline float3 Float3Up() {
	return float3(0.f, 1.f, 0.f);
}

inline float3 Float3Right() {
	return float3(1.f, 0.f, 0.f);
}

inline float3 TransformCoord(float3 vec, mat4 mat) {
	DirectX::XMVECTOR temp = DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&vec), mat);
	float3 tempOut;
	DirectX::XMStoreFloat3(&tempOut, temp);
	return tempOut;
}

inline float3 MultFloat3(float3 vec, float fl) {
	return float3(vec.x * fl, vec.y * fl, vec.z * fl);
}

inline float3 Float3MultFloat3(float3 a, float3 b) {
	return float3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline float clamp(float in, float a, float b) {
	float min = 0;
	float max = 0;
	if (a < b) {
		min = a;
		max = b;
	}
	else {
		min = b;
		max = a;
	}
	float result = in < min ? min : in;
	result = result > max ? max : result;
	return result;
}

inline float3 Float3Lerp(float3 minFl, float3 maxFl, float factor) {
	//print(minFl.z << " " << maxFl.z << " " << factor << " " << minFl.z + (maxFl.z - minFl.z) * factor);
	return float3(clamp(minFl.x + (maxFl.x - minFl.x) * factor, minFl.x, maxFl.x), 
		clamp(minFl.y + (maxFl.y - minFl.y) * factor, minFl.y, maxFl.y), 
		clamp(minFl.z + (maxFl.z - minFl.z) * factor, minFl.z, maxFl.z));
}

inline float DistanceFloat3(float3 a, float3 b) {
	return MagnitureFloat3(float3(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline float DotFloat3(float3 a, float3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float AngleFloat3Degree(float3 a, float3 b) {
	float up = DotFloat3(a, b);
	float down = MagnitureFloat3(a) * MagnitureFloat3(b);
	return RadiansToDegree(acosf(up / down));
}

inline float3 Float3Minus(float3 a, float3 b) {
	return float3(a.x-b.x, a.y-b.y, a.z-b.z);
}

inline float3 getSphereCenter(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	float x4, float y4, float z4)//空间四点确定球心坐标(克莱姆法则)
{
	float a11, a12, a13, a21, a22, a23, a31, a32, a33, b1, b2, b3, d, d1, d2, d3;
	a11 = 2 * (x2 - x1); a12 = 2 * (y2 - y1); a13 = 2 * (z2 - z1);
	a21 = 2 * (x3 - x2); a22 = 2 * (y3 - y2); a23 = 2 * (z3 - z2);
	a31 = 2 * (x4 - x3); a32 = 2 * (y4 - y3); a33 = 2 * (z4 - z3);
	b1 = x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1 + z2 * z2 - z1 * z1;
	b2 = x3 * x3 - x2 * x2 + y3 * y3 - y2 * y2 + z3 * z3 - z2 * z2;
	b3 = x4 * x4 - x3 * x3 + y4 * y4 - y3 * y3 + z4 * z4 - z3 * z3;
	d = a11 * a22*a33 + a12 * a23*a31 + a13 * a21*a32 - a11 * a23*a32 - a12 * a21*a33 - a13 * a22*a31;
	d1 = b1 * a22*a33 + a12 * a23*b3 + a13 * b2*a32 - b1 * a23*a32 - a12 * b2*a33 - a13 * a22*b3;
	d2 = a11 * b2*a33 + b1 * a23*a31 + a13 * a21*b3 - a11 * a23*b3 - b1 * a21*a33 - a13 * b2*a31;
	d3 = a11 * a22*b3 + a12 * b2*a31 + b1 * a21*a32 - a11 * b2*a32 - a12 * a21*b3 - b1 * a22*a31;
	float x = d1 / d;
	float y = d2 / d;
	float z = d3 / d;
	return float3(x, y, z);
}

inline float3 getSphereCenter(float3 a, float3 b, float3 c, float3 d) {
	return getSphereCenter(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, d.x, d.y, d.z);
}

inline float GetByIndex(float3 a, int index) {
	switch (index)
	{
	case 0:
		return a.x;
	case 1:
		return a.y;
	case 2:
		return a.z;
	default:
		print("Error index when GetByIndex for Vector3");
		return 0;
		break;
	}
}

struct ArcRay {
public:
	float3 origin;
	float3 direction;
};
/*
float3 RotationMatrixToEulerAngles(mat4 mat)
{
	float sy = sqrt(mat.at<double>(0, 0) * R.at<double>(0, 0) + R.at<double>(1, 0) * R.at<double>(1, 0));
	bool singular = sy < 1e-6; // If
	float x, y, z;
	if (!singular)
	{
		x = atan2(R.at<double>(2, 1), R.at<double>(2, 2));
		y = atan2(-R.at<double>(2, 0), sy);
		z = atan2(R.at<double>(1, 0), R.at<double>(0, 0));
	}
	else
	{
		x = atan2(-R.at<double>(1, 2), R.at<double>(1, 1));
		y = atan2(-R.at<double>(2, 0), sy);
		z = 0;
	}
#if 1
	x = x * 180.0f / 3.141592653589793f;
	y = y * 180.0f / 3.141592653589793f;
	z = z * 180.0f / 3.141592653589793f;
#endif
	return float3(x, y, z);
}
*/
