#pragma once
#include "ArcMath.h"

namespace DX11Engine {

	class ArcAABB
	{
	public:
		ArcAABB() {}
		ArcAABB(const float3 a, const float3 &b)
		{
			m_BoundMin = a; m_BoundMin = b;
		}

		
		float3 GetMin() const;
		float3 GetMax() const;

		bool hit(const ArcRay& r, float tmin, float tmax) const;

	private:
		float3 m_BoundMin;
		float3 m_BoundMax;
	};

}

