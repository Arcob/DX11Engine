#include "ArcRenderer.h"
#include "ArcStructures.h"
#include "ArcRHI.h"

namespace DX11Engine {

	layoutStruct::layoutStruct(int index, int size, int totalLength, int phase, int dataSize) : m_index(index), m_width(size), m_totalLength(totalLength), m_phase(phase), m_dataSize(dataSize) {}

	bool ArcRenderer::Render(std::shared_ptr<ArcMesh> pMesh, std::shared_ptr<ArcMaterial> pMaterial) {
		UINT stride = sizeof(Vertex);
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
		immediateContext->Draw(pMesh->m_vertexLength, 0);
		return true;
	}
}