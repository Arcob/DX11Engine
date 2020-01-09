cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

struct VertexIn
{
    float3 PosL  : POSITION;
        float4 Color : COLOR;
};

struct VertexOut
{
    float4 PosH  : SV_POSITION;
        float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	vout.PosH = mul(float4(vin.PosL, 1.0f), World);
	vout.PosH = mul(vout.PosH, View);
	vout.PosH = mul(vout.PosH, Projection);
    
    // Transform to homogeneous clip space.
    //vout.PosH = float4(vin.PosL, 1.0f);
	//vout.PosH = mul(vout.PosH, World);
    
    // Just pass vertex color into the pixel shader.
    vout.Color = vin.Color;
	//vout.Color = mul(float4(vin.PosL, 1.0f), World);
	//vout.Color = float4(vout.Color.r, vout.Color.g, vout.Color.b, 1);
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Color;
}
