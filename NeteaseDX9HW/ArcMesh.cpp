#include "ArcMesh.h"

namespace DX11Engine {

	ArcMesh::ArcMesh(std::string meshName, std::shared_ptr<ID3D11Buffer> vertexBuffer, std::shared_ptr <ID3D11Buffer> indexBuffer, std::shared_ptr <ID3D11InputLayout> inputLayout):
		m_meshName(meshName), m_pVertexBuffer(vertexBuffer), m_pIndexBuffer(indexBuffer), m_pInputLayout(inputLayout) {}
}