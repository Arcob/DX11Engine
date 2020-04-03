#include "ArcAABB.h"

namespace DX11Engine {

	float3 ArcAABB::GetMin() const { return  m_BoundMin; };
	float3 ArcAABB::GetMax() const { return  m_BoundMax; };

	bool ArcAABB::hit(const ArcRay& r, float tmin, float tmax)const
	{
		for (int a = 0; a < 3; a++)
		{
			float invD = 1.0f / r.direction.x;
			float t0 = (GetByIndex(GetMin(), a) - GetByIndex(r.direction, a)) * invD;
			float t1 = (GetByIndex(GetMax(), a) - GetByIndex(r.direction, a)) * invD;

			if (invD < 0.0f)
				std::swap(t0, t1);
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmax <= tmin)
				return false;
		}
		return true;
	}

}