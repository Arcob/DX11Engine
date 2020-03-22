#pragma once

#include "CommonHeaders.h"

class ArcRenderToTexture
{
private:
	ID3D11ShaderResourceView* mShaderResourceView;  //Shader资源视图
	ID3D11Texture2D* mDepthStencilTexture;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mViewPort; //视口
	std::vector<D3D11_VIEWPORT> mipViewPortVector;
	std::vector<ID3D11Texture2D*> mipDepthStencilTextureVector;
	std::vector<ID3D11DepthStencilView*> mipDepthStencilViewVector;

public:
	ArcRenderToTexture();
	ArcRenderToTexture(const ArcRenderToTexture&other);
	~ArcRenderToTexture();
	bool InitializeAsDepthBuffer(ID3D11Device* d3dDevice, int TextureWidth, int TexureHeight, int mipLevel);
	void ShutDown();

	void SetRenderTarget(ID3D11DeviceContext* deviceContext, int mipLevel);
	void ClearRenderTarget(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha);
	void GenerateNewMip(ID3D11Device* d3dDevice, int TextureWidth, int TexureHeight, int mipLevel);
	void SetMipRenderTarget(ID3D11DeviceContext* deviceContext, int mipLevel);
	bool WriteToSubResource(ID3D11DeviceContext* deviceContext, int level);
	void ClearMipRenderTarget(ID3D11DeviceContext* deviceContext, int index);
	ID3D11ShaderResourceView* GetShaderResourceView();

};

