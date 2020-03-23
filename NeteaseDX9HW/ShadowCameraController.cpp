#include "ShadowCameraController.h"
#include "ArcGameObject.h"
#include "ArcBehaviour.h"
#include "ArcTransform.h"

void ShadowCameraController::Awake() {
	//print("Awake");
}

void ShadowCameraController::Start() {
	cachedMainCamera = DX11Engine::ArcGameObject::Find("Camera")->getComponent<DX11Engine::ArcCamera>();
	cachedDirectionalLight = DX11Engine::ArcGameObject::Find("Directional Light")->getComponent<DX11Engine::DirectionalLight>();
	//camera->TransformPtr()->RotateAround(DX11Engine::ArcGameObject::Find("TestBoxWithNormal")->TransformPtr()->Position(), Float3Up(), 45.0f);
	
	//print("Start");
}

void ShadowCameraController::Update() {
	SetCurLightInfo();
}

float MinInArray(float* array, int size) {
	float result = FLT_MAX;
	for (int i = 0; i < size; ++i) {
		if (array[i] < result) {
			result = array[i];
		}
	}
	return result;
}

float MaxInArray(float* array, int size) {
	float result = FLT_MIN;
	for (int i = 0; i < size; ++i) {
		if (array[i] > result) {
			result = array[i];
		}
	}
	return result;
}

void ShadowCameraController::SetCurLightInfo() {
	auto corner = cachedMainCamera->GetFrustumCorners(); //获取世界空间中主摄像机视锥的8个顶点
	DX11Engine::ArcCamera::FrustumCorners lightCorner = DX11Engine::ArcCamera::FrustumCorners();
	for (int i = 0; i < 4; i++)
	{
		lightCorner.nearCorners[i] = TransformCoord(corner->nearCorners[i], cachedDirectionalLight->View());
		lightCorner.farCorners[i] = TransformCoord(corner->farCorners[i], cachedDirectionalLight->View());
	}

	float xs[8] = { lightCorner.nearCorners[0].x, lightCorner.nearCorners[1].x, lightCorner.nearCorners[2].x, lightCorner.nearCorners[3].x,
					lightCorner.farCorners[0].x, lightCorner.farCorners[1].x, lightCorner.farCorners[2].x, lightCorner.farCorners[3].x };

	float ys[8] = { lightCorner.nearCorners[0].y, lightCorner.nearCorners[1].y, lightCorner.nearCorners[2].y, lightCorner.nearCorners[3].y,
					lightCorner.farCorners[0].y, lightCorner.farCorners[1].y, lightCorner.farCorners[2].y, lightCorner.farCorners[3].y };

	float zs[8] = { lightCorner.nearCorners[0].z, lightCorner.nearCorners[1].z, lightCorner.nearCorners[2].z, lightCorner.nearCorners[3].z,
					lightCorner.farCorners[0].z, lightCorner.farCorners[1].z, lightCorner.farCorners[2].z, lightCorner.farCorners[3].z };

	float minX = MinInArray(xs, 8);
	float maxX = MaxInArray(xs, 8);
	float minY = MinInArray(ys, 8);
	float maxY = MaxInArray(ys, 8);
	float minZ = MinInArray(zs, 8);
	float maxZ = MaxInArray(zs, 8);

	lightCorner.nearCorners[0] = float3(minX, minY, minZ);
	lightCorner.nearCorners[1] = float3(maxX, minY, minZ);
	lightCorner.nearCorners[2] = float3(maxX, maxY, minZ);
	lightCorner.nearCorners[3] = float3(minX, maxY, minZ);

	lightCorner.farCorners[0] = float3(minX, minY, maxZ);
	lightCorner.farCorners[1] = float3(maxX, minY, maxZ);
	lightCorner.farCorners[2] = float3(maxX, maxY, maxZ);
	lightCorner.farCorners[3] = float3(minX, maxY, maxZ);

	float3 pos = AddFloat3(lightCorner.nearCorners[0], MultFloat3(Float3Minus(lightCorner.nearCorners[2], lightCorner.nearCorners[0]), 0.5f));
	cachedDirectionalLight->GameObject()->TransformPtr()->SetPosition(TransformCoord(pos, Inverse(cachedDirectionalLight->View())));// = dirLightCamera.transform.TransformPoint(pos);
	cachedDirectionalLight->m_orthoCamPara = float4(maxX-minX, maxY-minY, 0, maxZ - minZ);
}