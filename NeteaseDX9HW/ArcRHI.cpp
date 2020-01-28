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
		GetClientRect((HWND)m_windowsHandle, &rc);//��ȡ���ڿͻ�����С
		//m_width = rc.right - rc.left;
		//m_height = rc.bottom - rc.top;
		m_width = rc.right - rc.left;
		m_height = rc.bottom - rc.top;
	}

	void ArcRHI::ConfigPhysicsDevice() {
		//dx11û��������
	}

	void ArcRHI::ConfigLogicalDevice() {
		createDeviceFlags = 0;
#ifdef _DEBUG
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//������������
		driverTypes.push_back(D3D_DRIVER_TYPE_HARDWARE);
		driverTypes.push_back(D3D_DRIVER_TYPE_WARP);
		driverTypes.push_back(D3D_DRIVER_TYPE_REFERENCE);

		numDriverTypes = driverTypes.size();
	}

	void ArcRHI::ConfigFeatureLevel() {
		//������������
		featureLevels.push_back(D3D_FEATURE_LEVEL_11_0);
		featureLevels.push_back(D3D_FEATURE_LEVEL_10_1);
		featureLevels.push_back(D3D_FEATURE_LEVEL_10_0);

		numFeatureLevels = featureLevels.size();
	}

	void ArcRHI::ConfigSwapChain() {
		g_swapChainDescription = new DXGI_SWAP_CHAIN_DESC();
		ZeroMemory(g_swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));//���
		g_swapChainDescription->BufferCount = 1;                              //����ֻ����һ���󻺳壨˫���壩���Ϊ1
		g_swapChainDescription->BufferDesc.Width = m_width;
		g_swapChainDescription->BufferDesc.Height = m_height;
		g_swapChainDescription->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		g_swapChainDescription->BufferDesc.RefreshRate.Numerator = 60;
		g_swapChainDescription->BufferDesc.RefreshRate.Denominator = 1;
		g_swapChainDescription->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		g_swapChainDescription->OutputWindow = (HWND)m_windowsHandle;
		g_swapChainDescription->SampleDesc.Count = 1;						 //1�ز���
		g_swapChainDescription->SampleDesc.Quality = 0;                      //�����ȼ�
		g_swapChainDescription->SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		 //���ò���
		g_swapChainDescription->Windowed = TRUE;                             //�Ƿ�ȫ��
	}

	long ArcRHI::CreateDeviceAndSwapChain() {
		long hResult;
		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
		{
			g_driverType = driverTypes[driverTypeIndex];
			hResult = D3D11CreateDeviceAndSwapChain(
				NULL,                                //Ĭ��ͼ��������
				g_driverType,                        //��������
				NULL,                                //ʵ�������Ⱦ�豸�Ķ�̬���������ʹ�õ������豸����������豸����ΪNULL
				createDeviceFlags,                   //������־��0������Ϸ������һ��D3D11_CREATE_DEVICE_DEBUG�������Ǵ����ɹ����Ե��豸���ڿ����бȽ�����
				featureLevels.data(),						//�����ȼ�
				numFeatureLevels,                    //�����ȼ�����
				D3D11_SDK_VERSION,                   //sdk�汾��
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
		//������ȾĿ����ͼ
		g_pBackBuffer = NULL;
		//��ȡ�󻺳�����ַ
		hResult = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&g_pBackBuffer);
		if (FAILED(hResult)) {
			return hResult;
		}

		//����Ŀ����ͼ
		hResult = g_pd3dDevice->CreateRenderTargetView(g_pBackBuffer, NULL, &g_pRenderTargetView);
		//�ͷź󻺳�
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
		//�󶨵���Ⱦ����
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
		//����viewport
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

		// ����ʹ�����ֵһ�µ����ؽ����滻�����/ģ��״̬
		// ��״̬���ڻ�����պУ���Ϊ���ֵΪ1.0ʱĬ���޷�ͨ����Ȳ���
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

		// �ޱ����޳�ģʽ
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

		// �ޱ����޳�ģʽ
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

