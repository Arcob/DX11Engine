#include "Light.h"
#include "ArcGameObject.h"
#include "ArcTransform.h"

namespace DX11Engine {
	DirectionalLight::DirectionalLight(float3 direction, float intensity, float4 color, float3 position, float4 cam) {
		Light::m_Type = LightType::TypeDirectionalLight;
		m_direction = direction;
		m_intensity = intensity;
		m_position = position;
		m_color = color;
		m_orthoCamPara = cam;
		lightCameraList = std::vector<std::shared_ptr<ArcOrthoCamera>>();
	}

	DirectionalLight::DirectionalLight(float intensity, float4 color, float4 cam) {
		Light::m_Type = LightType::TypeDirectionalLight;
		m_intensity = intensity;
		m_color = color;
		m_orthoCamPara = cam;
	}

	void DirectionalLight::AddCascadeCamera(std::shared_ptr<ArcOrthoCamera> camera, int level) {
		if (lightCameraList.size() > level) {
			print("Cascade camera level already exist");
			return;
		}
		camera->GameObject()->TransformPtr()->SetRotation(GameObject()->TransformPtr()->Rotation());
		lightCameraList.push_back(camera);
	}

	std::shared_ptr<ArcOrthoCamera> DirectionalLight::GetLightCamera(int level) {
		return lightCameraList[level];
	}

	mat4 DirectionalLight::View() {
		/*float3 up = GameObject()->TransformPtr()->Up();
		float3 forward = GameObject()->TransformPtr()->Forward();
		float3 lookatPos = AddFloat3(forward, GameObject()->TransformPtr()->Position());
		return CalculateViewMatrix(GameObject()->TransformPtr()->Position(), lookatPos, up);*/
		return View(0);
	}

	mat4 DirectionalLight::Orthographic() {
		//return CalculateOrthographicMatrix(m_orthoCamPara.x, m_orthoCamPara.y, m_orthoCamPara.z, m_orthoCamPara.w);
		return Orthographic(0);
	}

	mat4 DirectionalLight::View(int level) {
		return lightCameraList[level]->View();
	}

	mat4 DirectionalLight::Orthographic(int level) {
		return lightCameraList[level]->Projection();
	}
}