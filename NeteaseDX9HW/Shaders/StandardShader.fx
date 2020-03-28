Texture2D gTex : register(t0);
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

float CSMCalculation(float4 worldPos, float bias){
	float shadow = 0.0;
	//float blendTime = 0.0;
	for (int i = 0; i < 4; ++i){
		float4 lightSpacePos = mul(worldPos, LightMatrix[i]);
		float3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
		projCoords = float3(projCoords.x * 0.5f + 0.5f, projCoords.y * -0.5f + 0.5f, projCoords.z);
		//为啥光源空间深度会大于一，大于1为啥会出bug
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
					// 	shadow += (projCoords.z - bias) > pcfDepth ? 1.0 : 0.0;
					// if (tempUV.x > 0.0 & tempUV.x < 1.0 
					// & tempUV.y > 0.0 & tempUV.y < 1.0 ){
					// 	float pcfDepth = gShadowMap1.SampleLevel(gSamLinear, tempUV, i).r;
					// 	tempShadowSum += (projCoords.z - bias) > pcfDepth ? 1.0 : 0.0;
					// 	divide += 1.0;
					// }
				}
			}
			tempShadowSum /= 9.0;
			shadow += tempShadowSum;

			//blendTime++;
			//float closestDepth = gShadowMap1.SampleLevel(gSamLinear, projCoords.xy, i).r;
			//shadow = (projCoords.z - bias) > closestDepth ? 1.0f : 0.0f;
			//shadow = i;
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
	//vout.LightSpacePos = mul(mul(mul(float4(vin.Pos, 1.0f), World), View), Projection);
	vout.Normal = normalize(mul(vin.Normal, (float3x3)World));

    vout.Color = float4(vin.Tangent, 1.0f);
	vout.Tex = vin.Tex;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float bias = 0.00002f;
	float4 Albedo = gTex.Sample(gSamLinear, pin.Tex);
	//float4 Albedo = gShadowMap1.Sample(gSamLinear, pin.Tex);
	float diffuseIntensity = saturate(dot(pin.Normal, normalize(-LightDir)));
	float3 diffuse = diffuseIntensity * LightColor.rgb * Intensity;
	//float shadow = ShadowCalculation(pin.LightSpacePos, flag, bias);
	float shadow = CSMCalculation(pin.WorldPos, bias);
	//result += (1.0 - shadow) * diffuse;
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

	//return float4(shadow, shadow, shadow, 1);
    return float4(result, 1.0f);
	//return debugColor;
	//return gShadowMap1.SampleLevel(gSamLinear, pin.Tex, 0);
	//return float4(pin.PosH.b/ pin.PosH.w, pin.PosH.b / pin.PosH.w, pin.PosH.b / pin.PosH.w, 1.0f);
}
