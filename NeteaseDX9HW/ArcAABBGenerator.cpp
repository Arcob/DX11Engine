#include "ArcAABBGenerator.h"

namespace DX11Engine {
	void ArcAABBGenerator::GenerateBoundingBox(ArcAABB& aabb, const mat4& transformMatrix, std::vector<float3>& posVec) {
		print("ArcAABBGenerator base class method");
	}

	void ArcNormalAABBGenerator::GenerateBoundingBox(ArcAABB& aabb, const mat4& transformMatrix, std::vector<float3>& posVec) {
		float minX = 1000000.0f;//��FLT_MIN�Ƚϴ�С���ܳ���Ҳ���ǿ��ܳ���FLT_MIN��10С����
		float minY = 1000000.0f;
		float minZ = 1000000.0f;
		float maxX = -1000000.0f;
		float maxY = -1000000.0f;
		float maxZ = -1000000.0f;
		//����Ҫ����transform��������
		std::vector<float3>& curVec = posVec;
		//print(FLT_MIN << " "<< FLT_MAX);
		for (int i = 0; i < curVec.size(); i++) {
			float3 tempWorldPos = TransformCoord(curVec[i], transformMatrix);
			if (tempWorldPos.x > maxX) {
				maxX = tempWorldPos.x;
			}
			if (tempWorldPos.y > maxY) {
				maxY = tempWorldPos.y;
			}
			if (tempWorldPos.z > maxZ) {
				maxZ = tempWorldPos.z;
			}
			if (tempWorldPos.x < minX) {
				minX = tempWorldPos.x;
			}
			if (tempWorldPos.y < minY) {
				minY = tempWorldPos.y;
			}
			if (tempWorldPos.z < minZ) {
				minZ = tempWorldPos.z;
			}
		}
		float3 minFloat = float3(minX, minY, minZ);
		float3 maxFloat = float3(maxX, maxY, maxZ);
		aabb = ArcAABB(minFloat, maxFloat);
	}
}