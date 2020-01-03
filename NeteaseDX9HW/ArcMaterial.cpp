#include "ArcMaterial.h"

namespace DX11Engine {

	ArcMaterial::ArcMaterial(std::string name, ID3D11VertexShader *pSolidColorVS, ID3D11PixelShader *pSolidColorPS, ID3D11InputLayout *pInputLayout):
		m_name(name),
		m_pInputLayout(pInputLayout),
		m_pSolidColorVS(pSolidColorVS),
		m_pSolidColorPS(pSolidColorPS) {}

}