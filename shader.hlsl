//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

cbuffer ViewBuffer : register(b1)
{
    matrix View;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

cbuffer CameraPosBuffer : register(b5)
{
    float3 cameraPosition;
}

cbuffer InverseTransport : register(b6)
{
    matrix Inverse;
}

// マテリアルバッファ
struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    int noTexSampling;
    int PolyLine;
    float Dummy; // 16byte境界用
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}

// ライト用バッファ
struct LIGHT
{
    float4 Direction[10];
    float4 Position[10];
    float4 Diffuse[10];
    float4 Ambient[10];
    float4 Specular[10];
    float4 Attenuation[10];
    int4 Flags[10];
    int Enable;
    int Dummy[2]; // 16byte境界用
};

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}


//=============================================================================
// 頂点シェーダ
//=============================================================================
void VertexShaderPolygon(in float4 inPosition : POSITION0,
                        in float4 inNormal : NORMAL0,
                        in float4 inDiffuse : COLOR0,
                        in float2 inTexCoord : TEXCOORD0,

                        out float4 outPosition : SV_POSITION,
                        out float3 outNormal : NORMAL0,
                        out float2 outTexCoord : TEXCOORD0,
                        out float3 outViewDir : TEXCOORD1,
                        out float4 outDiffuse : COLOR0)
{
    matrix mvp;
    mvp = mul(World, mul(View, Projection));
    outPosition = mul(inPosition, mvp);
    outNormal = normalize(mul(inNormal.xyz, (float3x3) Inverse));
    outViewDir = normalize(cameraPosition - inPosition.xyz);
    outDiffuse = inDiffuse;
    outTexCoord = inTexCoord;
}

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

//=============================================================================
// ピクセルシェーダ
//=============================================================================
void PixelShaderPolygon(in float4 inPosition : SV_POSITION,
                        in float3 inNormal : NORMAL0,
                        in float2 inTexCoord : TEXCOORD0,
                        in float3 inViewDir : TEXCOORD1,
                        in float4 inDiffuse : COLOR0,

                        out float4 outDiffuse : SV_Target)
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    if (Light.Enable == 0)
    {
        color = Material.Diffuse;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            
            if (Light.Flags[i].y == 1)
            {
                if (Light.Flags[i].x == 1) // Directional Light
                {
                    float3 lightDirection = normalize(-Light.Direction[i].xyz);
                    float3 reflectDir = reflect(-lightDirection, inNormal);
                    float3 halfVector = normalize(lightDirection + inViewDir);
                    float specIntensity = pow(max(dot(halfVector, inNormal), 0.0), 5); // ｼﾆﾋ羣ﾟｹ簓ｿｶﾈ
                    float3 diff = mul(Material.Diffuse.rgb, max(0, dot(inNormal, lightDirection)));
                    float3 spec = specIntensity * Light.Specular[i].xyz * Material.Specular.xyz;
                    float3 abim = mul(Material.Ambient.rgb, Light.Ambient[i].rgb);
                    color += float4(abim + diff +spec, 1.0);
                }
                else if (Light.Flags[i].x == 2) // Point Light
                {
                    float3 lightDirection = normalize(Light.Position[i].xyz - inPosition.xyz);
                    float distance = length(Light.Position[i].xyz - inPosition.xyz);
                    float attenuation = 1.0 / (Light.Attenuation[i].x + Light.Attenuation[i].y * distance + Light.Attenuation[i].z * distance * distance);

                    float3 norm = normalize(inNormal);
                    float diffIntensity = max(dot(norm, lightDirection), 0.0);
                    float3 diffuse = diffIntensity * Light.Diffuse[i].xyz * Material.Diffuse.xyz;

                    float3 viewDir = normalize(inViewDir);
                    float3 reflectDir = reflect(-lightDirection, norm);
                    float specIntensity = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);
                    float3 specular = specIntensity * Light.Specular[i].xyz * Material.Specular.xyz;

                    color += attenuation * float4(diffuse + specular, 1.0);
                }
            }
        }
    }

    if (Material.noTexSampling == 0)
    {
        float4 texColor = g_Texture.Sample(g_SamplerState, inTexCoord);
        if (Material.PolyLine == 0)
        {
            color *= texColor*Material.Diffuse ;
        }
        
        else if (Material.PolyLine == 1)
        {
            color = Material.Diffuse*inDiffuse ;
        }
    }
    else
    {
        color *= inDiffuse;
    }

    color += Material.Emission;
    outDiffuse = color;
}
