#include "ArcRenderToTexture.h"

ArcRenderToTexture::ArcRenderToTexture()
{
	mShaderResourceView = NULL;
	mDepthStencilTexture = NULL;
	mDepthStencilView = NULL;

}


ArcRenderToTexture::ArcRenderToTexture(const ArcRenderToTexture&other)
{

}

ArcRenderToTexture::~ArcRenderToTexture()
{

}


bool ArcRenderToTexture::InitializeAsDepthBuffer(ID3D11Device* d3dDevice, int TextureWidth, int TexureHeight , int mipLevel)
{
	//CreateTexture2D��������һ����ͼ
	//CreateDepthStencilView��������һ������д�����ͼ����֮ǰ��������ͼ�󶨣���dx�Ѷ���д�������ͼʱ���Զ�д���󶨵���ͼ��
	//CreateShaderResourceView��������һ�������������ͼ����֮ǰ��������ͼ�󶨣����ڰ���ͼ�����ݴ���shader

	//��һ,��������ͼ��2D�����������ṹ��,������2D��Ⱦ����
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = TextureWidth;
	depthBufferDesc.Height = TexureHeight;
	depthBufferDesc.MipLevels = mipLevel;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS; //24λ��Ϊ����Ȼ��棬8λ��Ϊ��ģ�建��
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;  //ע����Ȼ���(����)�İ󶨱�־
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	HR(d3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &mDepthStencilTexture));


	//�ڶ�,�����Ȼ�����ͼ�������ṹ��,��������Ȼ�����ͼ
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	HR(d3dDevice->CreateDepthStencilView(mDepthStencilTexture, &depthStencilViewDesc, &mDepthStencilView));
	

	//����,�����ɫ����Դ��ͼ������,�����д�����ɫ����Դ��ͼ,ע����������Ȼ���(����)�������ģ���������ȾĿ�껺��(����)������
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS; //��ʱ��Ϊ�ǽ����������д����������ɫд�����Դ�ʱShader��Դ��ʽ����Ȼ�����һ����
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = depthBufferDesc.MipLevels;
	HR(d3dDevice->CreateShaderResourceView(mDepthStencilTexture, &shaderResourceViewDesc, &mShaderResourceView));

	//���ģ������ӿڵ�����
	mViewPort.Width = (float)TextureWidth;
	mViewPort.Height = (float)TexureHeight;
	mViewPort.MinDepth = 0.0f;
	mViewPort.MaxDepth = 1.0f;
	mViewPort.TopLeftX = 0.0f;
	mViewPort.TopLeftY = 0.0f;

	return true;
}

void ArcRenderToTexture::GenerateNewMip(ID3D11Device* d3dDevice, int TextureWidth, int TexureHeight, int mipLevel) {
	for (int i = 0; i < mipLevel; i++) {
		ID3D11DepthStencilView* tempDSV = NULL;
		ID3D11Texture2D* tempTexture = NULL;

		D3D11_VIEWPORT tempViewport;
		tempViewport.Width = (float)TextureWidth / (2 << i);
		tempViewport.Height = (float)TexureHeight / (2 << i);
		tempViewport.MinDepth = 0.0f;
		tempViewport.MaxDepth = 1.0f;
		tempViewport.TopLeftX = 0.0f;
		tempViewport.TopLeftY = 0.0f;

		D3D11_TEXTURE2D_DESC depthBufferDesc;
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
		depthBufferDesc.Width = TextureWidth / (2 << i);
		depthBufferDesc.Height = TexureHeight / (2 << i);
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS; //24λ��Ϊ����Ȼ��棬8λ��Ϊ��ģ�建��
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;  //ע����Ȼ���(����)�İ󶨱�־
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;
		HR(d3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &tempTexture));


		//�ڶ�,�����Ȼ�����ͼ�������ṹ��,��������Ȼ�����ͼ
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		HR(d3dDevice->CreateDepthStencilView(tempTexture, &depthStencilViewDesc, &tempDSV));

		mipViewPortVector.push_back(tempViewport);
		mipDepthStencilTextureVector.push_back(tempTexture);
		mipDepthStencilViewVector.push_back(tempDSV);
	}
}

void ArcRenderToTexture::SetMipRenderTarget(ID3D11DeviceContext* deviceContext, int mipLevel) {
	ID3D11RenderTargetView* renderTarget[1] = { 0 };

	//����ȾĿ����ͼ�����ģ����ͼ�������Ⱦ����
	deviceContext->OMSetRenderTargets(1, renderTarget, mipDepthStencilViewVector[mipLevel-1]);

	//�����ӿ�
	deviceContext->RSSetViewports(1, &(mipViewPortVector[mipLevel - 1]));
}

bool ArcRenderToTexture::WriteToSubResource(ID3D11DeviceContext* deviceContext, int mipLevel) {
	ID3D11Resource *pSrcResource;
	mipDepthStencilViewVector[mipLevel - 1]->GetResource(&pSrcResource);

	ID3D11Resource *pDstResource;
	mShaderResourceView->GetResource(&pDstResource);

	deviceContext->CopySubresourceRegion(pDstResource, mipLevel, 0, 0, 0, pSrcResource, 0, NULL);
	return false;
}

#define ReleaseCOM(x) { if (x) { x->Release(); x = 0; } }

void ArcRenderToTexture::ShutDown()
{
	ReleaseCOM(mDepthStencilTexture);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mShaderResourceView);
}


//�ô�ʱ����ͼ����Ⱦ�����Ŀǰ��Ⱦ��λ��
void ArcRenderToTexture::SetRenderTarget(ID3D11DeviceContext* deviceContext, int mipLevel)
{
	ID3D11RenderTargetView* renderTarget[1] = { 0 };

	//����ȾĿ����ͼ�����ģ����ͼ�������Ⱦ����
	deviceContext->OMSetRenderTargets(1, renderTarget, mDepthStencilView);

	//�����ӿ�
	deviceContext->RSSetViewports(1, &mViewPort);
}

void ArcRenderToTexture::ClearMipRenderTarget(ID3D11DeviceContext* deviceContext, int mipLevel)
{
	//�����Ȼ����ģ�建��
	deviceContext->ClearDepthStencilView(mipDepthStencilViewVector[mipLevel - 1], D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//����������󻺴�,��Ϊ����Ҫ����ɫд(ColorWrite),�����������д
void ArcRenderToTexture::ClearRenderTarget(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
	//�����������Ϊ����ɫ
	float color[4];
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;


	//�����Ȼ����ģ�建��
	deviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

// ��������Ⱦģ�͵������������ΪShaderResourceView��Դ���أ������Դ�����������ShaderResourceView��Դһ��������Shader�����.
ID3D11ShaderResourceView* ArcRenderToTexture::GetShaderResourceView()
{
	return mShaderResourceView;
}