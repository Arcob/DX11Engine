Texture2D gTex : register(t1);
Texture2D gShadowMap1 : register(t2);
SamplerState gSamLinear : register(s0);
SamplerState gSamLinearShadow : register(s1);

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
	matrix LightMatrix[4];
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
	float4 WorldPos : TEXCOORD4;
	float4 LightSpacePos : TEXCOORD5;
};

float3 Ambient = float3(0.1f, 0.1f, 0.1f);

float CSMCalculation(float4 worldPos, float bias){
	float shadow = 0.0;
	for (int i = 0; i < 4; ++i){
		float4 lightSpacePos = mul(worldPos, LightMatrix[i]);
		float3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
		projCoords = float3(projCoords.x * 0.5f + 0.5f, projCoords.y * -0.5f + 0.5f, projCoords.z);
		
		if (projCoords.x > 0.01 & projCoords.x < 0.99 
		& projCoords.y > 0.01 & projCoords.y < 0.99 
		& projCoords.z > 0.0 & projCoords.z < 1.0
		){
			uint width = 1;
			uint height = 1;
			uint numberOfLevel = 1;
			float divide = 0.0;
			gShadowMap1.GetDimensions(i, width, height, numberOfLevel);
			float2 texelSize = float2(1.0f / width, 1.0f / height);
			float tempShadowSum = 0.0;
			for (int x = -1; x <= 1; ++x)
			{
				for (int y = -1; y <= 1; ++y)
				{
					float2 tempUV = projCoords.xy + float2(x, y) * texelSize;
					float pcfDepth = gShadowMap1.SampleLevel(gSamLinearShadow, tempUV, i).r;
					tempShadowSum += (projCoords.z - bias) > pcfDepth ? 0.9 : 0.0;/**/
				}
			}
			tempShadowSum /= 9.0;
			shadow += tempShadowSum;

			break;
		}
	}
	return shadow;
}

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	vout.PosH = mul(float4(vin.Pos, 1.0f), World);
	vout.WorldPos = vout.PosH;
	vout.LightSpacePos = mul(vout.PosH, LightMatrix[0]);
	vout.PosH = mul(vout.PosH, View);
	vout.PosH = mul(vout.PosH, Projection);
	vout.Normal = normalize(mul(vin.Normal, (float3x3)World));

    vout.Color = float4(vin.Tangent, 1.0f);
	vout.Tex = vin.Tex;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float bias = 0.00002f;
	float4 Albedo = gTex.Sample(gSamLinear, pin.Tex);
	float diffuseIntensity = saturate(dot(pin.Normal, normalize(-LightDir)));
	float3 diffuse = diffuseIntensity * LightColor.rgb * Intensity;
	float shadow = CSMCalculation(pin.WorldPos, bias);
	float3 result = (1.0 - shadow) * Albedo.rgb * (0.5f + diffuse) + Ambient;
	
	float4 debugColor;
	
	if (shadow < 0.1){
		debugColor = float4(1.0, 0, 0, 1.0);
	}else if (shadow < 1.1){
		debugColor = float4(0.0, 1.0, 0, 1.0);
	}else if (shadow < 2.1){
		debugColor = float4(0.0, 0.0, 1.0, 1.0);
	}else{
		debugColor = float4(0.0, 1.0, 1.0, 1.0);
	}

    return float4(result, 1.0f);
}
