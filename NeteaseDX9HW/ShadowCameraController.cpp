#include "ShadowCameraController.h"
#include "ArcGameObject.h"
#include "ArcBehaviour.h"
#include "ArcTransform.h"
#include "DriverSetting.h"

void ShadowCameraController::Awake() {
	//print("Awake");
}

void ShadowCameraController::Start() {
	cachedMainCamera = DX11Engine::ArcGameObject::Find("Camera")->getComponent<DX11Engine::ArcPrespCamera>();
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

#define USE_SPHERE false

#if USE_SPHERE

void ShadowCameraController::SetCurLightInfo() {
	std::vector<std::shared_ptr<DX11Engine::ArcPrespCamera::FrustumCorners>> frustumCornerList = std::vector<std::shared_ptr<DX11Engine::ArcPrespCamera::FrustumCorners>>();
	cachedMainCamera->GetCascadeFrustumCornersList(frustumCornerList);
	
	for (int j = 0; j < frustumCornerList.size(); ++j) {
		DX11Engine::ArcPrespCamera::FrustumCorners lightCorner = DX11Engine::ArcPrespCamera::FrustumCorners();
		for (int i = 0; i < 4; i++)
		{
			lightCorner.nearCorners[i] = TransformCoord(frustumCornerList[j]->nearCorners[i], cachedDirectionalLight->GetLightCamera(j)->View());
			lightCorner.farCorners[i] = TransformCoord(frustumCornerList[j]->farCorners[i], cachedDirectionalLight->GetLightCamera(j)->View());
		}

		float3 centerInLightSpace = getSphereCenter(lightCorner.nearCorners[0], lightCorner.farCorners[0], lightCorner.farCorners[1], lightCorner.farCorners[2]);
		float radius = floor(DistanceFloat3(centerInLightSpace, lightCorner.nearCorners[0]));
		float treatedX = centerInLightSpace.x;
		float treatedY = centerInLightSpace.y;

		float fWorldUnitsPerTexel = 2.0f * radius / (float)SHADOW_MAP_WIDTH;

		treatedX /= fWorldUnitsPerTexel;
		treatedX = floor(treatedX);
		treatedX *= fWorldUnitsPerTexel;

		treatedY /= fWorldUnitsPerTexel;
		treatedY = floor(treatedY);
		treatedY *= fWorldUnitsPerTexel;

		float3 pos = float3(treatedX, treatedY, centerInLightSpace.z - radius);
		
		cachedDirectionalLight->GetLightCamera(j)->GameObject()->TransformPtr()->SetPosition(TransformCoord(pos, Inverse(cachedDirectionalLight->GetLightCamera(j)->View())));// = dirLightCamera.transform.TransformPoint(pos);
		cachedDirectionalLight->GetLightCamera(j)->SetOrthoPara(radius * 2.0f, radius * 2.0f, 0, radius * 2.0f);
	}
}
#else

void ShadowCameraController::SetCurLightInfo() {
	std::vector<std::shared_ptr<DX11Engine::ArcPrespCamera::FrustumCorners>> frustumCornerList = std::vector<std::shared_ptr<DX11Engine::ArcPrespCamera::FrustumCorners>>();
	cachedMainCamera->GetCascadeFrustumCornersList(frustumCornerList);

	for (int j = 0; j < frustumCornerList.size(); ++j) {
		DX11Engine::ArcPrespCamera::FrustumCorners lightCorner = DX11Engine::ArcPrespCamera::FrustumCorners();
		for (int i = 0; i < 4; i++)
		{
			lightCorner.nearCorners[i] = TransformCoord(frustumCornerList[j]->nearCorners[i], cachedDirectionalLight->GetLightCamera(j)->View());
			lightCorner.farCorners[i] = TransformCoord(frustumCornerList[j]->farCorners[i], cachedDirectionalLight->GetLightCamera(j)->View());
		}

		float farDist = DistanceFloat3(lightCorner.farCorners[0], lightCorner.farCorners[2]);
		float crossDist = DistanceFloat3(lightCorner.nearCorners[0], lightCorner.farCorners[2]);
		float maxDist = farDist > crossDist ? farDist : crossDist;

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

		float fWorldUnitsPerTexel = maxDist / (float)SHADOW_MAP_WIDTH;
		float posX = (minX + maxX)*0.5f;
		posX /= fWorldUnitsPerTexel;
		posX = floor(posX);
		posX *= fWorldUnitsPerTexel;

		float posY = (minY + maxY)*0.5f;
		posY /= fWorldUnitsPerTexel;
		posY = floor(posY);
		posY *= fWorldUnitsPerTexel;

		float posZ = minZ;
		posZ /= fWorldUnitsPerTexel;
		posZ = floor(posZ);
		posZ *= fWorldUnitsPerTexel;
		
		float3 center = float3(posX, posY, posZ);

		float3 pos = AddFloat3(lightCorner.nearCorners[0], MultFloat3(Float3Minus(lightCorner.nearCorners[2], lightCorner.nearCorners[0]), 0.5f));
		cachedDirectionalLight->GetLightCamera(j)->GameObject()->TransformPtr()->SetPosition(TransformCoord(center, Inverse(cachedDirectionalLight->GetLightCamera(j)->View())));
		cachedDirectionalLight->GetLightCamera(j)->SetOrthoPara(maxDist, maxDist, 0, maxZ - minZ);
	}
}
#endif // USE_SPHERE