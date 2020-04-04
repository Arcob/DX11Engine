#pragma once
#include "ArcMath.h"
#include "ArcAABB.h"
#include "ArcGameObject.h"

namespace DX11Engine {
	class ArcBvhNode;
	class ArcMesh;

	class HitRecord
	{
	public:
		HitRecord();
		std::shared_ptr<ArcBvhNode> hit;
	};

	class ArcBvhNode
	{
	public:
		ArcBvhNode() {};
		//virtual void GenerateBoundingBox(mat4 transformMatrix);
		//virtual bool Hit(const ArcRay& r, std::shared_ptr<HitRecord> &rec) const;
		//virtual std::shared_ptr<ArcAABB> bounding_box();

		std::shared_ptr<ArcBvhNode> left;
		std::shared_ptr <ArcBvhNode> right;
		ArcAABB aabb;
		//std::shared_ptr<ArcAABB> aabb = nullptr;
		ArcMesh* mesh;
	};
}

