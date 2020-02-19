#pragma once

#include "CommonHeaders.h"

class ArcRenderToTexture
{
private:
	ID3D11ShaderResourceView* mShaderResourceView;  //Shader资源视图
	ID3D11Texture2D* mDepthStencilTexture;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mViewPort; //视口

public:
	ArcRenderToTexture();
	ArcRenderToTexture(const ArcRenderToTexture&other);
	~ArcRenderToTexture();
	bool Initialize(ID3D11Device* d3dDevice, int TextureWidth, int TexureHeight);
	void ShutDown();

	void SetRenderTarget(ID3D11DeviceContext* deviceContext);
	void ClearRenderTarget(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha);
	ID3D11ShaderResourceView* GetShaderResourceView();

};

