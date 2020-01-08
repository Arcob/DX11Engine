#include "ArcMaterial.h"

namespace DX11Engine {

	ArcMaterial::ArcMaterial(std::string name, ID3D11VertexShader *pSolidColorVS, ID3D11PixelShader *pSolidColorPS, ID3D11InputLayout *pInputLayout, ID3D11Buffer* pMVPConstantBuffer):
		m_name(name),
		m_pInputLayout(pInputLayout),
		m_pVertexShader(pSolidColorVS),
		m_pPixelShader(pSolidColorPS),
		m_pMVPConstantBuffer(pMVPConstantBuffer)
	{
	}

}