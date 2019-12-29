#include "ArcFramework.h"
#include "ArcWindow.h"

time_t ArcFramework::initTime = 0;

int ArcFramework::init() {
	initTime = clock();
	return 1;
}

std::shared_ptr<ArcWindow> ArcFramework::showWindows(std::string name, int height, int width) {
	std::shared_ptr<ArcWindow> pWindow = std::make_shared<ArcWindow>(name, height, width);
	pWindow->DX11createWindow();
	return pWindow;
}

void ArcFramework::configInput(int height, int width) {

}

time_t ArcFramework::getTime() {
	return clock() - initTime;
}

void ArcFramework::termiate() {

}