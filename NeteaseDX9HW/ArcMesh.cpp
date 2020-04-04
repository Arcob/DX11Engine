#include "ArcMesh.h"

namespace DX11Engine {

	/*ArcMesh::ArcMesh(std::string meshName, ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, ID3D11InputLayout* inputLayout):
		m_meshName(meshName), m_pVertexBuffer(vertexBuffer), m_pIndexBuffer(indexBuffer), m_pInputLayout(inputLayout) {}*/

	ArcMesh::ArcMesh(std::string meshName, ID3D11Device* device) : m_meshName(meshName), m_device(device){}

	ArcMesh::ArcMesh(std::string meshName, ID3D11Device* device, std::shared_ptr<ArcAABBGenerator> aabbGenerator) : m_meshName(meshName), m_device(device), aabbGenerator(aabbGenerator){}

	bool ArcMesh::BindVertexBuffer(void* vertexs, unsigned int length) {
		long result;
		//m_nodeLength = length;

		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.ByteWidth = length;
		

		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = vertexs;
		result = m_device->CreateBuffer(&vertexDesc, &resourceData, &m_pVertexBuffer);
		if (result < 0)
		{
			return false;
		}
		return true;
	}

	bool ArcMesh::BindIndexBuffer(unsigned int* indices, unsigned int length) {
		long result;
		m_indexLength = length;

		D3D11_BUFFER_DESC indexDesc;
		ZeroMemory(&indexDesc, sizeof(indexDesc));
		indexDesc.Usage = D3D11_USAGE_IMMUTABLE;
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.ByteWidth = sizeof(UINT) * length;

		D3D11_SUBRESOURCE_DATA indexData;
		ZeroMemory(&indexData, sizeof(indexData));
		indexData.pSysMem = indices;
		result = m_device->CreateBuffer(&indexDesc, &indexData, &m_pIndexBuffer);
		if (result < 0)
		{
			return false;
		}
		return true;
	}
}