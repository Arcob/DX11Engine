#pragma once
#include "ArcBehaviour.h"
#include "ArcMath.h"

namespace DX11Engine {
	enum CameraType
	{
		Perspective = 0,
		Orthographic = 1
	};

	class ArcCameraBase :
		public DX11Engine::ArcBehaviour
	{	

	public:
		CameraType cameraType;
		virtual mat4 const Matrix() = 0;
		virtual mat4 const Projection() = 0;
		virtual mat4 const View() = 0;

	private:
		//float m_nearPlane;
		//float m_farPlane;
	};
}


