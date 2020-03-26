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
	//CreateTexture2D创建的是一个贴图
	//CreateDepthStencilView创建的是一个用于写入的视图，与之前创建的贴图绑定，当dx把东西写入这个视图时会自动写到绑定的贴图上
	//CreateShaderResourceView创建的是一个用于输出的视图，与之前创建的贴图绑定，用于把贴图的内容传入shader

	//第一,填充深度视图的2D纹理描述符结构体,并创建2D渲染纹理
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = TextureWidth;
	depthBufferDesc.Height = TexureHeight;
	depthBufferDesc.MipLevels = mipLevel;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS; //24位是为了深度缓存，8位是为了模板缓存
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;  //注意深度缓存(纹理)的绑定标志
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	HR(d3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &mDepthStencilTexture));


	//第二,填充深度缓存视图描述符结构体,并创建深度缓存视图
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	HR(d3dDevice->CreateDepthStencilView(mDepthStencilTexture, &depthStencilViewDesc, &mDepthStencilView));
	

	//第三,填充着色器资源视图描述符,并进行创建着色器资源视图,注意这是用深度缓存(纹理)来创建的，而不是渲染目标缓存(纹理)创建的
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS; //此时因为是仅仅进行深度写，而不是颜色写，所以此时Shader资源格式跟深度缓存是一样的
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = depthBufferDesc.MipLevels;
	HR(d3dDevice->CreateShaderResourceView(mDepthStencilTexture, &shaderResourceViewDesc, &mShaderResourceView));

	//第四，设置视口的属性
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
		depthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS; //24位是为了深度缓存，8位是为了模板缓存
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;  //注意深度缓存(纹理)的绑定标志
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;
		HR(d3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &tempTexture));


		//第二,填充深度缓存视图描述符结构体,并创建深度缓存视图
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

	//绑定渲染目标视图和深度模板视图到输出渲染管线
	deviceContext->OMSetRenderTargets(1, renderTarget, mipDepthStencilViewVector[mipLevel-1]);

	//设置视口
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


//让此时所有图形渲染到这个目前渲染的位置
void ArcRenderToTexture::SetRenderTarget(ID3D11DeviceContext* deviceContext, int mipLevel)
{
	ID3D11RenderTargetView* renderTarget[1] = { 0 };

	//绑定渲染目标视图和深度模板视图到输出渲染管线
	deviceContext->OMSetRenderTargets(1, renderTarget, mDepthStencilView);

	//设置视口
	deviceContext->RSSetViewports(1, &mViewPort);
}

void ArcRenderToTexture::ClearMipRenderTarget(ID3D11DeviceContext* deviceContext, int mipLevel)
{
	//清除深度缓存和模板缓存
	deviceContext->ClearDepthStencilView(mipDepthStencilViewVector[mipLevel - 1], D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//不用清除背后缓存,因为不需要进颜色写(ColorWrite),仅仅进行深度写
void ArcRenderToTexture::ClearRenderTarget(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
	//设置清除缓存为的颜色
	float color[4];
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;


	//清除深度缓存和模板缓存
	deviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

// 将“被渲染模型到纹理的纹理”作为ShaderResourceView资源返回，这个资源将会跟其它的ShaderResourceView资源一样被送入Shader里计算.
ID3D11ShaderResourceView* ArcRenderToTexture::GetShaderResourceView()
{
	return mShaderResourceView;
}