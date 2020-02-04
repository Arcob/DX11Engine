Texture2D gTex : register(t0);
SamplerState gSamLinear : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

cbuffer DirectionLight : register(b1) 
{
	float3 LightDir;
	float Intensity;
	float4 LightColor;
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
	float2 Tex : TEXCOORD2;
	float3 Normal : TEXCOORD3;
};

float4 Ambient = float4(0.1f, 0.1f, 0.1f, 1.0f);

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	vout.PosH = mul(float4(vin.Pos, 1.0f), World);
	vout.PosH = mul(vout.PosH, View);
	vout.PosH = mul(vout.PosH, Projection);
	vout.Normal = normalize(mul(vin.Normal, (float3x3)World));

    vout.Color = float4(vin.Tangent, 1.0f);
	vout.Tex = vin.Tex;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 Albedo = gTex.Sample(gSamLinear, pin.Tex);
	float diffuseIntensity = saturate(dot(pin.Normal, normalize(LightDir)));
	float3 diffuse = diffuseIntensity * LightColor.rgb * Intensity;
	float3 result = Albedo.rgb +diffuse + Ambient.rgb;

    return float4(result, 1.0f);
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(pin.PosH.x, pin.PosH.y, pin.PosH.z, 1.0f);
	//return float4(diffuseIntensity, diffuseIntensity, diffuseIntensity, 1.0f);
}
