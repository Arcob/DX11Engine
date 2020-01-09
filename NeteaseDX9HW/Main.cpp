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

using namespace DX11Engine;

bool SetupRenderHardwareInterface(size_t windowsHandle);

const int WIDTH = 1024, HEIGHT = 768;
float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
std::shared_ptr<ArcWindow> pWindow;
std::shared_ptr<ArcAssets> assets;
std::shared_ptr<ArcApplication> app;
bool isRunning = false;

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

	//app = std::make_shared<Application>();
	
	while (isRunning) 
	{
		pWindow->TreatMessage(isRunning);
		ArcTime::Update((float)ArcFramework::getTime());
		ArcRHI::ClearScreen(clearColor);

		for (auto gameObject : app->MainScene()->GetGameObjectsInScene()) { //渲染
			if (gameObject->Mesh() != nullptr && gameObject->Material() != nullptr) {
				DX11Engine::ArcRenderer::Render(gameObject->Mesh(), gameObject->Material(), gameObject->TransformPtr(), app->MainScene()->GetMainCamera());
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
	if (FAILED(ArcRHI::CreateRenderView())) {
		return false;
	}
	ArcRHI::ConfigViewPort(0.0f, 1.0f, 0, 0);
	return true;
}



