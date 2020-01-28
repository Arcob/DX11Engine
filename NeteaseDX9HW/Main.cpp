// NeteaseDX9HW.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "CommonHeaders.h"
#include "ArcFramework.h"
#include "ArcWindow.h"


#include "ArcRHI.h"

#include "ArcTime.h"
#include "DriverSetting.h"
#include "ArcScene.h"
#include "ArcRenderer.h"
#include "ArcGameObject.h"
#include "ArcInput.h"
#include "ArcAssetLoader.h"
#include "CommonStates.h"

using namespace DX11Engine;

bool SetupRenderHardwareInterface(size_t windowsHandle);

//const int WIDTH = 1024, HEIGHT = 768;
float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
std::shared_ptr<ArcWindow> pWindow;
std::shared_ptr<ArcAssets> assets;
std::shared_ptr<ArcApplication> app;
bool isRunning = false;

std::unique_ptr <DirectX::CommonStates> m_states;

int main()
{
	isRunning = true;
	ArcFramework::init();
	pWindow = ArcFramework::showWindows("Test window", WIDTH, HEIGHT);
	if (!SetupRenderHardwareInterface(pWindow->GetHandle())) {
		print("Error! When Setup Render Hardware Interface");
	}
	else {
		print("Setup Render Hardware Interface Correct");
	}

	assets = std::make_shared<Assets>(); //加载资源
	app = std::make_shared<Application>(WIDTH, HEIGHT, assets); //加载应用

	ArcInput::Init(pWindow);

	for (auto gameObject : app->MainScene()->GetGameObjectsInScene()) { //渲染
		for (auto behaviour : gameObject->GetBehaviourList()) {
			behaviour->Awake();
		}
	}

	for (auto gameObject : app->MainScene()->GetGameObjectsInScene()) { //渲染
		for (auto behaviour : gameObject->GetBehaviourList()) {
			behaviour->Start();
		}
	}

	std::string catMeshPath = DX11Engine::ArcTool::getCurrentPath() + DX11Engine::ArcAssetLoader::MODEL_PATH + "cat.cmo";
	auto pCatMesh = DX11Engine::ArcAssetLoader::LoadModelFormFileInner(catMeshPath);

	m_states = std::make_unique<DirectX::CommonStates>(ArcRHI::g_pd3dDevice);/**/

	while (isRunning) 
	{
		pWindow->TreatMessage(isRunning);
		ArcTime::Update((float)ArcFramework::getTime());
		ArcInput::Update();
		ArcRHI::ClearScreen(clearColor);

		for (auto gameObject : app->MainScene()->GetGameObjectsInScene()) { //Update
			for (auto behaviour : gameObject->GetBehaviourList()) {
				behaviour->Update();
			}
		}

		FL(ArcRHI::ConfigRasterizerStateCullNone());

		auto pSkybox = ArcGameObject::Find("SkyBox");
		if (pSkybox->Mesh() != nullptr && pSkybox->Material() != nullptr) {
			DX11Engine::ArcRenderer::Render(pSkybox->Mesh(), pSkybox->Material(), pSkybox->TransformPtr(), app->MainScene()->GetMainCamera(), app->MainScene()->GetMainLight());
		}

		//画模型加载的猫
		auto pCatTransform = ArcGameObject::Find("Cat")->TransformPtr();
		//PrintFloat3(pCatTransform->Rotation());
		ConstantBufferMvp cbMVP;
		cbMVP.mWorld = pCatTransform->TransformMatrix();//DX的mvp要反着乘
		cbMVP.mView = app->MainScene()->GetMainCamera()->View();
		cbMVP.mProjection = app->MainScene()->GetMainCamera()->Projection();
		pCatMesh->Draw(ArcRHI::g_pImmediateContext, *m_states, cbMVP.mWorld, cbMVP.mView, cbMVP.mProjection, false);/**/

		FL(ArcRHI::ConfigRasterizerStateCullBack());

		
		
		//PrintFloat3(app->MainScene()->GetMainCamera()->GameObject()->TransformPtr()->Position());
		for (auto gameObject : app->MainScene()->GetGameObjectsInScene()) { //渲染
			if (gameObject->name() == "SkyBox") {
				continue;
			}
			if (gameObject->Mesh() != nullptr && gameObject->Material() != nullptr) {
				DX11Engine::ArcRenderer::Render(gameObject->Mesh(), gameObject->Material(), gameObject->TransformPtr(), app->MainScene()->GetMainCamera(), app->MainScene()->GetMainLight());
			}		
		}
		ArcRHI::SwapChainPresent();
		
	}
	//pWindow->Run();
	/*
	std::cout << ArcFramework::getTime() << std::endl;
	std::cout << time(0) << std::endl;2q3
	*/
}

bool SetupRenderHardwareInterface(size_t windowsHandle) {
	ArcRHI::Init(windowsHandle);
	ArcRHI::ConfigPhysicsDevice();
	ArcRHI::ConfigLogicalDevice();
	ArcRHI::ConfigFeatureLevel();
	ArcRHI::ConfigSwapChain();
	if (ArcRHI::CreateDeviceAndSwapChain() < 0) {
		return false;
	}
	if (ArcRHI::CreateRenderView() < 0) {
		return false;
	}
	if (!ArcRHI::ConfigDepthStencilState()) {
		return false;
	}
	
	ArcRHI::ConfigViewPort(0.0f, 1.0f, 0, 0);
	return true;
}



