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
    float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	vout.PosH = mul(float4(vin.Pos, 1.0f), World);
	vout.PosH = mul(vout.PosH, View);
	vout.PosH = mul(vout.PosH, Projection);

    vout.Color = float4(vin.Tangent, 1.0f);
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Color;
}
