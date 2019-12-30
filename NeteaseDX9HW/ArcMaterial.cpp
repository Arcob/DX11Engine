#include "ArcMaterial.h"

ArcMaterial::ArcMaterial(ID3D11Buffer *pVertexBuffer, ID3D11InputLayout *pInputLayout, ID3D11VertexShader *pSolidColorVS, ID3D11PixelShader *pSolidColorPS):
	m_pVertexBuffer(pVertexBuffer),
	m_pInputLayout(pInputLayout),
	m_pSolidColorVS(pSolidColorVS),
	m_pSolidColorPS(pSolidColorPS) {}