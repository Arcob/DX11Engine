// NeteaseDX9HW.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "CommonHeaders.h"
#include "ArcFramework.h"
#include "ArcWindow.h"
#include "ArcRHI.h"

bool SetupRenderHardwareInterface(size_t windowsHandle);

const int WIDTH = 1024, HEIGHT = 768;
std::shared_ptr<ArcWindow> pWindow;
bool isRunning = false;

int main()
{
	isRunning = true;
	ArcFramework::init();
	pWindow = ArcFramework::showWindows("Test window", WIDTH, HEIGHT);
	if (!SetupRenderHardwareInterface(pWindow->GetHandle())) {
		print("Error");
	}
	else {
		print("Correct");
	}
	//ArcFramework::configInput(0, 0);
	while (isRunning)
	{
		pWindow->TreatMessage(isRunning);
		
	}
	//pWindow->Run();
	/*
	std::cout << ArcFramework::getTime() << std::endl;
	std::cout << time(0) << std::endl;
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
		print("b");
		return false;
	}
	ArcRHI::CreateViewPort();
	
}


