#pragma once
#include "ArcBehaviour.h"
#include "ArcMath.h"

namespace DX11Engine {

	class ArcOrthoCamera :
		public DX11Engine::ArcBehaviour
	{
	public:
		ArcOrthoCamera();
		ArcOrthoCamera(float width, float height, float nearZ, float farZ);
		void SetOrthoPara(float width, float height, float nearZ, float farZ);

		mat4 Matrix() const;
		mat4 Projection() const;
		mat4 View() const;

	private:
		float m_width;
		float m_height;
		float m_nearPlane;
		float m_farPlane;
	};

}

