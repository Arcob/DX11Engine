#pragma once
#include "ArcMath.h"
#include "ArcAABB.h"

namespace DX11Engine {

	class ArcBvhNode
	{
	public:
		ArcBvhNode() {};
		bool hit(const ArcRay& r, ArcBvhNode* &rec)const;
		bool bounding_box(ArcAABB &box) const;

		ArcBvhNode* left;
		ArcBvhNode* right;
		ArcAABB aabb;

	private:
		
	};

}

