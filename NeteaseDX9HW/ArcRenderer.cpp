#include "ArcRenderer.h"
#include "ArcStructures.h"
#include "ArcRHI.h"

namespace DX11Engine {

	layoutStruct::layoutStruct(int index, int size, int totalLength, int phase, int dataSize) : m_index(index), m_width(size), m_totalLength(totalLength), m_phase(phase), m_dataSize(dataSize) {}

	bool ArcRenderer::Render(std::shared_ptr<ArcMesh> pMesh, std::shared_ptr<ArcMaterial> pMaterial, std::shared_ptr<ArcTransform> pTransform, std::shared_ptr<ArcCamera> pCamera) {
		UINT stride = pMesh->m_nodeLength;
		UINT offset = 0;
		//设置数据信息格式控制信息
		auto immediateContext = ArcRHI::g_pImmediateContext;
		immediateContext->IASetInputLayout(pMaterial->m_pInputLayout);
		//设置要绘制的几何体信息
		immediateContext->IASetVertexBuffers(0, 1, &pMesh->m_pVertexBuffer, &stride, &offset);
		immediateContext->IASetIndexBuffer(pMesh->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		//指明如何绘制三角形
		immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		immediateContext->VSSetShader(pMaterial->m_pVertexShader, 0, 0);
		immediateContext->PSSetShader(pMaterial->m_pPixelShader, 0, 0);
		immediateContext->VSSetConstantBuffers(0, 1, &pMaterial->m_pMVPConstantBuffer);//设置mvp buffer为buffer0

		ConstantBuffer cb;
		cb.mWorld = Transpose(pTransform->transformMatrix());//DX的mvp要反着乘
		cb.mView = Transpose(pCamera->View());
		cb.mProjection = Transpose(pCamera->Projection());

		D3D11_MAPPED_SUBRESOURCE mappedData;
		long result = immediateContext->Map(pMaterial->m_pMVPConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
		if (FAILED(result)) {
			print("Map buffer false");
		}
		memcpy_s(mappedData.pData, sizeof(cb), &cb, sizeof(cb));
		immediateContext->Unmap(pMaterial->m_pMVPConstantBuffer, 0);

		immediateContext->UpdateSubresource(pMaterial->m_pMVPConstantBuffer, 0, NULL, &cb, 0, 0);

		immediateContext->DrawIndexed(pMesh->m_indexLength, 0, 0);
		return true;
	}
}