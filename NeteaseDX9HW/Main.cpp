﻿// NeteaseDX9HW.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "CommonHeaders.h"
#include "ArcFramework.h"
#include "ArcWindow.h"
#include "ArcRHI.h"
#include "ArcTime.h"

bool SetupRenderHardwareInterface(size_t windowsHandle);

const int WIDTH = 1024, HEIGHT = 768;
float clearColor[4] = { 0.5f, 0.1f, 0.2f, 1.0f };
std::shared_ptr<ArcWindow> pWindow;
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
	
	while (isRunning) 
	{
		pWindow->TreatMessage(isRunning);
		ArcTime::Update(ArcFramework::getTime());

		ArcRHI::ClearScreen(clearColor);
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
	if (FAILED(ArcRHI::CreateRenderView())) {
		return false;
	}
	ArcRHI::ConfigViewPort(0.0f, 1.0f, 0, 0);
	
}

