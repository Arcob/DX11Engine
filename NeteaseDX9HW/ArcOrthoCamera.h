#pragma once
#include "ArcBehaviour.h"
#include "ArcCameraBase.h"
#include "ArcMath.h"

namespace DX11Engine {

	class ArcOrthoCamera :
		public ArcCameraBase
	{
	public:
		ArcOrthoCamera();
		ArcOrthoCamera(float width, float height, float nearZ, float farZ);
		void SetOrthoPara(float width, float height, float nearZ, float farZ);

		virtual void Awake();
		virtual void EarlyUpdate();

		virtual mat4 const Matrix();
		virtual mat4 const Projection();
		virtual mat4 const View();
		mat4 const CalView();
		mat4 const CalProjection();

	private:
		float m_width;
		float m_height;
		float m_nearPlane;
		float m_farPlane;
	};

}

