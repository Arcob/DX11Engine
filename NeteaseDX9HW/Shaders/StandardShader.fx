Texture2D gTex : register(t0);
Texture2D gShadowMap1 : register(t2);
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
	float3 LightPosition;
	float Pad1;
	matrix LightMatrix;
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
	float4 LightSpacePos : TEXCOORD4;
};

float3 Ambient = float3(0.1f, 0.1f, 0.1f);

float ShadowCalculation(float4 lightSpacePos, float viewDepth, float bias)
{
	float shadow = 0.0;
	// ?????????
	float3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
	// ?��??[0,1]???��
	projCoords = float3(projCoords.x * 0.5f + 0.5f, projCoords.y * -0.5f + 0.5f, projCoords.z);
	// ????????????(???[0,1]??��???fragPosLight??????)
	//float closestDepth = gShadowMap1.Sample(gSamLinear, projCoords.xy).r;
	// ????????????????????
	float currentDepth = projCoords.z;
	// ??�n?????????????
	//shadow = (currentDepth - bias) > closestDepth ? 1.0f : 0.0f;
	//float a = 1 * 0;
	//uint cascadeLevel = clamp(a, 0, 3);
	//uint cascadeLevel = abs(currentDepth * 0.5f + 0.8f);
	uint cascadeLevel = 0;

	uint width = 1.0;
	uint height = 1.0;
	gShadowMap1.GetDimensions(width, height);
	float2 texelSize = float2(1.0f / width, 1.0f / height);
	float pcfDepth;
	for (int x = -2; x <= 2; ++x)
	{
		for (int y = -2; y <= 2; ++y)
		{
			//float pcfDepth = curTex.Sample(gSamLinear, projCoords.xy + float2(x, y) * texelSize).r;
			float pcfDepth = gShadowMap1.SampleLevel(gSamLinear, projCoords.xy + float2(x, y) * texelSize, viewDepth * 3.0).r;
			// ??�n?????????????
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 25.0;

	if (projCoords.z > 1.0) {
		shadow = 0.0;
	}

	return shadow;
}

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	vout.PosH = mul(float4(vin.Pos, 1.0f), World);
	vout.LightSpacePos = mul(vout.PosH, LightMatrix);
	vout.PosH = mul(vout.PosH, View);
	vout.PosH = mul(vout.PosH, Projection);
	//vout.LightSpacePos = mul(mul(mul(float4(vin.Pos, 1.0f), World), View), Projection);
	vout.Normal = normalize(mul(vin.Normal, (float3x3)World));

    vout.Color = float4(vin.Tangent, 1.0f);
	vout.Tex = vin.Tex;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float bias = 0.00005f;
	float4 Albedo = gTex.Sample(gSamLinear, pin.Tex);
	//float4 Albedo = gShadowMap1.Sample(gSamLinear, pin.Tex);
	float diffuseIntensity = saturate(dot(pin.Normal, normalize(-LightDir)));
	float3 diffuse = diffuseIntensity * LightColor.rgb * Intensity;
	//float3 diffuse = float3(1.0f, 1.0f, 0.0f);
	float shadow = ShadowCalculation(pin.LightSpacePos, pin.PosH.b / pin.PosH.w, bias);
	//result += (1.0 - shadow) * diffuse;
	float3 result = (1.0 - shadow) * Albedo.rgb * (0.5f + diffuse) + Ambient;
	
    return float4(result, 1.0f);
	//return gShadowMap1.SampleLevel(gSamLinear, pin.Tex, 1);
	//return float4(pin.PosH.b/ pin.PosH.w, pin.PosH.b / pin.PosH.w, pin.PosH.b / pin.PosH.w, 1.0f);
}
