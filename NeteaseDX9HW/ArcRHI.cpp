#include "ArcRHI.h"

size_t ArcRHI::m_windowsHandle = 0;
unsigned int ArcRHI::m_width = 0;
unsigned int ArcRHI::m_height = 0;
unsigned int ArcRHI::createDeviceFlags = 0;
unsigned int ArcRHI::numDriverTypes = 0;
unsigned int ArcRHI::numFeatureLevels = 0;
D3D_DRIVER_TYPE ArcRHI::g_driverType = (D3D_DRIVER_TYPE)0;
IDXGISwapChain* ArcRHI::g_pSwapChain(NULL);
ID3D11Device* ArcRHI::g_pd3dDevice(NULL);
D3D_FEATURE_LEVEL ArcRHI::g_featureLevel = (D3D_FEATURE_LEVEL)0;
DXGI_SWAP_CHAIN_DESC* ArcRHI::g_swapChainDescription(NULL);
ID3D11DeviceContext* ArcRHI::g_pImmediateContext(NULL);
ID3D11RenderTargetView* ArcRHI::g_pRenderTargetView(NULL);
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

long ArcRHI::CreateRenderView() {//����
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

	//�󶨵���Ⱦ����
	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
	return hResult;
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
	g_pSwapChain->Present(0, 0);
}
