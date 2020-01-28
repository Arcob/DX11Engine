#include "ArcRHI.h"

namespace DX11Engine {

	size_t ArcRHI::m_windowsHandle = 0;
	unsigned int ArcRHI::m_width = 0;
	unsigned int ArcRHI::m_height = 0;
	unsigned int ArcRHI::createDeviceFlags = 0;
	unsigned int ArcRHI::numDriverTypes = 0;
	unsigned int ArcRHI::numFeatureLevels = 0;
	ID3D11DepthStencilState* ArcRHI::DDSLessEqual(NULL);
	ID3D11RasterizerState* ArcRHI::RSNoCull(NULL);
	D3D_DRIVER_TYPE ArcRHI::g_driverType = (D3D_DRIVER_TYPE)0;
	IDXGISwapChain* ArcRHI::g_pSwapChain(NULL);
	ID3D11Device* ArcRHI::g_pd3dDevice(NULL);
	D3D_FEATURE_LEVEL ArcRHI::g_featureLevel = (D3D_FEATURE_LEVEL)0;
	DXGI_SWAP_CHAIN_DESC* ArcRHI::g_swapChainDescription(NULL);
	ID3D11DeviceContext* ArcRHI::g_pImmediateContext(NULL);
	ID3D11RenderTargetView* ArcRHI::g_pRenderTargetView(NULL);
	ID3D11Texture2D * ArcRHI::g_pDepthStencilBuffer(NULL);
	ID3D11DepthStencilView* ArcRHI::g_pDepthStencilView(NULL);
	ID3D11Texture2D* ArcRHI::g_pBackBuffer(NULL);
	std::vector<D3D_DRIVER_TYPE> ArcRHI::driverTypes(0);
	std::vector<D3D_FEATURE_LEVEL> ArcRHI::featureLevels(0);

#ifdef WORKING_ON_WINDOWS
	HWND ArcRHI::m_tempPlatformHandle = nullptr;
#endif // WORKING_ON_WINDOWS

	void ArcRHI::Init(size_t handle) {
		RECT rc;
		m_windowsHandle = handle;
		GetClientRect((HWND)m_windowsHandle, &rc);//获取窗口客户区大小
		//m_width = rc.right - rc.left;
		//m_height = rc.bottom - rc.top;
		m_width = rc.right - rc.left;
		m_height = rc.bottom - rc.top;
	}

	void ArcRHI::ConfigPhysicsDevice() {
		//dx11没得这玩意
	}

	void ArcRHI::ConfigLogicalDevice() {
		createDeviceFlags = 0;
#ifdef _DEBUG
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//驱动类型数组
		driverTypes.push_back(D3D_DRIVER_TYPE_HARDWARE);
		driverTypes.push_back(D3D_DRIVER_TYPE_WARP);
		driverTypes.push_back(D3D_DRIVER_TYPE_REFERENCE);

		numDriverTypes = driverTypes.size();
	}

	void ArcRHI::ConfigFeatureLevel() {
		//特征级别数组
		featureLevels.push_back(D3D_FEATURE_LEVEL_11_0);
		featureLevels.push_back(D3D_FEATURE_LEVEL_10_1);
		featureLevels.push_back(D3D_FEATURE_LEVEL_10_0);

		numFeatureLevels = featureLevels.size();
	}

	void ArcRHI::ConfigSwapChain() {
		g_swapChainDescription = new DXGI_SWAP_CHAIN_DESC();
		ZeroMemory(g_swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));//填充
		g_swapChainDescription->BufferCount = 1;                              //我们只创建一个后缓冲（双缓冲）因此为1
		g_swapChainDescription->BufferDesc.Width = m_width;
		g_swapChainDescription->BufferDesc.Height = m_height;
		g_swapChainDescription->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		g_swapChainDescription->BufferDesc.RefreshRate.Numerator = 60;
		g_swapChainDescription->BufferDesc.RefreshRate.Denominator = 1;
		g_swapChainDescription->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		g_swapChainDescription->OutputWindow = (HWND)m_windowsHandle;
		g_swapChainDescription->SampleDesc.Count = 1;						 //1重采样
		g_swapChainDescription->SampleDesc.Quality = 0;                      //采样等级
		g_swapChainDescription->SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		 //常用参数
		g_swapChainDescription->Windowed = TRUE;                             //是否全屏
	}

	long ArcRHI::CreateDeviceAndSwapChain() {
		long hResult;
		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
		{
			g_driverType = driverTypes[driverTypeIndex];
			hResult = D3D11CreateDeviceAndSwapChain(
				NULL,                                //默认图形适配器
				g_driverType,                        //驱动类型
				NULL,                                //实现软件渲染设备的动态库句柄，如果使用的驱动设备类型是软件设备则不能为NULL
				createDeviceFlags,                   //创建标志，0用于游戏发布，一般D3D11_CREATE_DEVICE_DEBUG允许我们创建可供调试的设备，在开发中比较有用
				featureLevels.data(),						//特征等级
				numFeatureLevels,                    //特征等级数量
				D3D11_SDK_VERSION,                   //sdk版本号
				g_swapChainDescription,
				&g_pSwapChain,
				&g_pd3dDevice,
				&g_featureLevel,
				&g_pImmediateContext
			);
			if (SUCCEEDED(hResult))
				break;
		}
		if (FAILED(hResult))
			return hResult;
	}

	long ArcRHI::CreateRenderView() {
		long hResult;
		//创建渲染目标视图
		g_pBackBuffer = NULL;
		//获取后缓冲区地址
		hResult = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&g_pBackBuffer);
		if (FAILED(hResult)) {
			return hResult;
		}

		//创建目标视图
		hResult = g_pd3dDevice->CreateRenderTargetView(g_pBackBuffer, NULL, &g_pRenderTargetView);
		//释放后缓冲
		g_pBackBuffer->Release();
		if (FAILED(hResult)) {
			return hResult;
		}

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.Width = m_width;
		depthStencilDesc.Height = m_height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		HR(g_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &g_pDepthStencilBuffer));

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthStencilDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		HR(g_pd3dDevice->CreateDepthStencilView(g_pDepthStencilBuffer, &descDSV, &g_pDepthStencilView));
		g_pDepthStencilBuffer->Release();
		//绑定到渲染管线
		g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

		//g_pd3dDevice->setrenders
		return hResult;
	}

	long ArcRHI::CreateDepthStencilView() {
		return 1;
	}

	void ArcRHI::ResetDepthStencilState() {
		g_pImmediateContext->OMSetDepthStencilState(nullptr, 0);
	}

	void ArcRHI::ConfigViewPort(float minDepth, float maxDepth, float topLeftX, float topLeftY) {
		//设置viewport
		D3D11_VIEWPORT vp;
		vp.Height = (float)m_height;
		vp.Width = (float)m_width;
		vp.MinDepth = minDepth;
		vp.MaxDepth = maxDepth;
		vp.TopLeftX = topLeftX;
		vp.TopLeftY = topLeftY;
		g_pImmediateContext->RSSetViewports(1, &vp);
	}

	long ArcRHI::ConfigDepthStencilState() {
		D3D11_DEPTH_STENCIL_DESC dsDesc;

		// 允许使用深度值一致的像素进行替换的深度/模板状态
		// 该状态用于绘制天空盒，因为深度值为1.0时默认无法通过深度测试
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		//dsDesc.FrontFace = true;


		dsDesc.StencilEnable = false;

		if (g_pd3dDevice->CreateDepthStencilState(&dsDesc, &DDSLessEqual) < 0) {
			print("CreateDepthStencilState Error");
			return false;
		}

		g_pImmediateContext->OMSetDepthStencilState(DDSLessEqual, 0);
		return true;
	}

	long ArcRHI::ConfigRasterizerStateCullNone() {
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

		// 无背面剔除模式
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.DepthClipEnable = true;

		if (g_pd3dDevice->CreateRasterizerState(&rasterizerDesc, &RSNoCull) < 0) {
			print("CreateRasterizerState Error");
			return false;
		}

		g_pImmediateContext->RSSetState(RSNoCull);
		return true;
	}

	long ArcRHI::ConfigRasterizerStateCullBack() {
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

		// 无背面剔除模式
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.DepthClipEnable = true;

		if (g_pd3dDevice->CreateRasterizerState(&rasterizerDesc, &RSNoCull) < 0) {
			print("CreateRasterizerState Error");
			return false;
		}

		g_pImmediateContext->RSSetState(RSNoCull);
		return true;
	}

	void ArcRHI::CleanUp() {
		if (g_pImmediateContext)
			g_pImmediateContext->ClearState();
		if (g_pSwapChain)
			g_pSwapChain->Release();
		if (g_pRenderTargetView)
			g_pRenderTargetView->Release();
		if (g_pImmediateContext)
			g_pImmediateContext->Release();
		if (g_pd3dDevice)
			g_pd3dDevice->Release();
	}

	void ArcRHI::ClearScreen(float ClearColor[4]) {
		//float ClearColor[4] = { 0.5f, 0.1f, 0.2f, 1.0f }; //red,green,blue,alpha
		g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
		g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		//g_pSwapChain->Present(0, 0);
	}

	void ArcRHI::SwapChainPresent() {
		g_pSwapChain->Present(0, 0);
	}
}

