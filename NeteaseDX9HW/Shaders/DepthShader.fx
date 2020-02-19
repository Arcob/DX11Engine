
cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

struct VertexIn
{
	float3 Pos  : POSITION;
	float3 Normal : NORMAL;
	float3 Tangent : TEXCOORD0;
	float2 Tex : TEXCOORD1;
};

struct VertexOut
{
	float4 Pos:SV_POSITION;
	float4 color:COlOR;
};

VertexOut VS(VertexIn ina)
{
	VertexOut outa;
	outa.Pos = mul(float4(ina.Pos,1.0f), World);
	outa.Pos = mul(outa.Pos, View);
	outa.Pos = mul(outa.Pos, Projection);
	outa.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	return outa;
}

float4 PS(VertexOut outa) : SV_Target
{
	return outa.color;
}