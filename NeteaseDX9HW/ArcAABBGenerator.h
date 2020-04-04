#pragma once
#include "ArcMath.h"
#include "ArcAABB.h"

namespace DX11Engine {

	class ArcAABBGenerator
	{
	public:
		ArcAABBGenerator() {};
		virtual void GenerateBoundingBox(ArcAABB& aabb, const mat4& transformMatrix, std::vector<float3>& posVec);
	};

	class ArcNormalAABBGenerator :
		public ArcAABBGenerator
	{
	public:
		ArcNormalAABBGenerator() {};
		virtual void GenerateBoundingBox(ArcAABB& aabb, const mat4& transformMatrix, std::vector<float3>& posVec);
	};

}

