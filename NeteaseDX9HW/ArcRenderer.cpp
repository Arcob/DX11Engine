#include "ArcRenderer.h"
#include "ArcStructures.h"
#include "memory.h"
#include "ArcRHI.h"

namespace DX11Engine {

	layoutStruct::layoutStruct(int index, int size, int totalLength, int phase, int dataSize) : m_index(index), m_width(size), m_totalLength(totalLength), m_phase(phase), m_dataSize(dataSize) {}
	std::unique_ptr <DirectX::CommonStates> ArcRenderer::m_states;

	bool ArcRenderer::Render(std::shared_ptr<ArcMesh> pMesh, std::shared_ptr<ArcMaterial> pMaterial, std::shared_ptr<ArcTransform> pTransform, std::shared_ptr<ArcCamera> pCamera, std::shared_ptr<DirectionalLight> pMainLight) {
		UINT stride = pMesh->m_nodeLength;
		UINT offset = 0;
		//设置数据信息格式控制信息
		auto immediateContext = ArcRHI::g_pImmediateContext;

		//immediateContext->RSSetState(nullptr);
		//immediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

		immediateContext->IASetInputLayout(pMaterial->m_pInputLayout);
		//设置要绘制的几何体信息
		immediateContext->IASetVertexBuffers(0, 1, &pMesh->m_pVertexBuffer, &stride, &offset);
		immediateContext->IASetIndexBuffer(pMesh->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		//指明如何绘制三角形
		immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		immediateContext->VSSetShader(pMaterial->m_pVertexShader, 0, 0);
		immediateContext->PSSetShader(pMaterial->m_pPixelShader, 0, 0);
		immediateContext->VSSetConstantBuffers(0, 1, &pMaterial->m_pMVPConstantBuffer);//设置mvp buffer为buffer0
		immediateContext->PSSetConstantBuffers(1, 1, &pMaterial->m_pMainLightConstantBuffer);//设置Light buffer为buffer1 光照在pshader用所以用PSSet
		
		ConstantBufferMvp cbMVP;
		cbMVP.mWorld = Transpose(pTransform->TransformMatrix());//DX的mvp要反着乘
		cbMVP.mView = Transpose(pCamera->View());
		cbMVP.mProjection = Transpose(pCamera->Projection());

		//PrintMat(cbMVP.mWorld);

		SetConstantBuffer(immediateContext, pMaterial->m_pMVPConstantBuffer, &cbMVP, sizeof(cbMVP));

		ConstantBufferLight cbl;
		cbl.Direction = pMainLight->m_direction;
		cbl.Intensity = pMainLight->m_intensity;
		cbl.Color = pMainLight->m_color;

		SetConstantBuffer(immediateContext, pMaterial->m_pMainLightConstantBuffer, &cbl, sizeof(cbl));

		immediateContext->DrawIndexed(pMesh->m_indexLength, 0, 0);
		return true;
	}

	bool ArcRenderer::SetConstantBuffer(ID3D11DeviceContext* immediateContext, ID3D11Buffer* constantBuffer, void* resources, size_t size) {
		D3D11_MAPPED_SUBRESOURCE mappedData;
		long result = immediateContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		if (FAILED(result)) {
			print("Map buffer false");
			return false;
		}
		memcpy_s(mappedData.pData, size, resources, size);
		immediateContext->Unmap(constantBuffer, 0);

		immediateContext->UpdateSubresource(constantBuffer, 0, NULL, resources, 0, 0);
		return true;
	}

	void ArcRenderer::RenderLoadedMesh(std::unique_ptr<DirectX::Model> mesh, mat4 m, mat4 v, mat4 p) {
		if (m_states == nullptr) {
			m_states = std::make_unique<DirectX::CommonStates>(ArcRHI::g_pd3dDevice);
		}
		mesh->Draw(ArcRHI::g_pImmediateContext, *m_states, m, v, p);
	}
}