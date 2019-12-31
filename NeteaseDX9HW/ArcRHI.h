#pragma once

#include "ArcGraphicSetting.h"
#include "CommonHeaders.h"

#ifdef USING_DX11

#include <d3d11.h>
#include <dxerr.h>
#include <D3DX11.h>
#include "D3DCompiler.h"

#endif // USING_DX11

namespace DX11Engine {

	//RenderHardwareInterface
	class ArcRHI //跨平台强相关
	{
	public:
		static void Init(size_t handle);
		static void ConfigPhysicsDevice();
		static void ConfigLogicalDevice();
		static void ConfigFeatureLevel();
		static void ConfigSwapChain();
		static long CreateDeviceAndSwapChain();
		static long CreateRenderView();
		static void ConfigViewPort(float minDepth, float maxDepth, float topLeftX, float topLeftY);
		static void CleanUp();
		static void ClearScreen(float ClearColor[4]);


	private:
		static size_t m_windowsHandle;
		static unsigned int m_width;
		static unsigned int m_height;
		static unsigned int createDeviceFlags;
		static unsigned int numDriverTypes;
		static unsigned int numFeatureLevels;
		static D3D_DRIVER_TYPE g_driverType;
		static IDXGISwapChain* g_pSwapChain;
		static ID3D11Device* g_pd3dDevice;
		static D3D_FEATURE_LEVEL g_featureLevel;
		static DXGI_SWAP_CHAIN_DESC* g_swapChainDescription;
		static ID3D11DeviceContext* g_pImmediateContext;
		static ID3D11RenderTargetView* g_pRenderTargetView;
		static ID3D11Texture2D* g_pBackBuffer;
		static std::vector<D3D_DRIVER_TYPE> driverTypes;
		static std::vector<D3D_FEATURE_LEVEL> featureLevels;

#ifdef WORKING_ON_WINDOWS
		static HWND m_tempPlatformHandle;
#endif // WORKING_ON_WINDOWS

	};

}
