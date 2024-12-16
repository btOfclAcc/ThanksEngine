// applies post processing effects to a screen quad

cbuffer PostProcessBuffer : register(b0)
{
    float param0;
    float param1;
    float param2;
    float param3;
}

Texture2D textureMap0 : register(t0);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.texCoord = input.texCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 finalColor = 0.0f;
    float time = param1;
    
    // Curvature Distortion
    float curvatureStrength = param2;
    
    float2 center = float2(0.5f, 0.5f);
    float2 offset = input.texCoord - center;
    float dist = length(offset);
    float curvature = dist * dist * curvatureStrength;
    float2 curvedTexCoord = input.texCoord + normalize(offset) * curvature;
    
    float cornerDist = length(float2(1.0f, 1.0f) - center);
    float scaleFactor = 1.0f / (1.0f + curvatureStrength * cornerDist);
    
    curvedTexCoord = center + (curvedTexCoord - center) * scaleFactor;
    
    // Wave
    float waveNum = param3;
    float waveLength = 0.0001f;
    float waveSpeed = 100.0f;

    float waveValue = curvedTexCoord.y * (3.141592f * waveNum / 2.0f) + (time * waveSpeed);
    float2 waveTexCoord = curvedTexCoord;
    waveTexCoord.x += sin(waveValue) * waveLength;
    
    // Chromatic Aberration
    float2 distortion = float2(0.005f, -0.005f);
    float4 redChannel = textureMap0.Sample(textureSampler, waveTexCoord + distortion.x * input.texCoord);
    float4 greenChannel = textureMap0.Sample(textureSampler, waveTexCoord);
    float4 blueChannel = textureMap0.Sample(textureSampler, waveTexCoord + distortion.y * input.texCoord);
    float4 chromaticAberrationColor = float4(redChannel.r, greenChannel.g, blueChannel.b, 1.0f);
    
    // Blur
    float height = 9.0f;
    float width = 16.0f;
    float blurStrengthW = param0;
    float blurStrengthH = param0 * width / height;
    
    float u = waveTexCoord.x;
    float v = waveTexCoord.y;
    float4 blurColor =
        textureMap0.Sample(textureSampler, float2(u, v))
        + textureMap0.Sample(textureSampler, float2(u + blurStrengthW, v))
        + textureMap0.Sample(textureSampler, float2(u - blurStrengthW, v))
        + textureMap0.Sample(textureSampler, float2(u, v + blurStrengthH))
        + textureMap0.Sample(textureSampler, float2(u, v - blurStrengthH))
        + textureMap0.Sample(textureSampler, float2(u + blurStrengthW, v + blurStrengthH))
        + textureMap0.Sample(textureSampler, float2(u + blurStrengthW, v - blurStrengthH))
        + textureMap0.Sample(textureSampler, float2(u - blurStrengthW, v + blurStrengthH))
        + textureMap0.Sample(textureSampler, float2(u - blurStrengthW, v - blurStrengthH));
    blurColor *= 0.12f;
    
    // Color Blend
    float chromaticWeight = 0.5f;
    float blurWeight = 0.5f;
    
    finalColor = chromaticWeight * chromaticAberrationColor
       + blurWeight * blurColor;
    
    // Scanlines
    waveNum = param3;
    float scanlineStrengthHori = 0.4f;
    float scanlineStrengthVert = 0.025f;
    height = 9.0f;
    width = 16.0f;

    // Horizontal
    float scanlineFactor = -abs(sin(waveTexCoord.y * 3.141592f * (waveNum - 0.5f))) + 1.0f;
    finalColor *= (1.0f - scanlineFactor * scanlineStrengthHori);
    
    // Vertical
    scanlineFactor = -abs(sin(waveTexCoord.x * 3.141592f * (waveNum - 0.5f) * width / height)) + 1.0f;
    finalColor *= (1.0f - scanlineFactor * scanlineStrengthVert);
    
    // Hum Bar
    float humBarThickness = 0.03f;
    float humBarIntensity = 0.5f;
    float3 humbarColor = float3(0.1f, 0.1f, 0.1f);
    
    float humBarOffset = tan(time / 2.0f - 1.0f) / 2.0f + 0.5f;

    float humBar = step(abs(waveTexCoord.y - humBarOffset), humBarThickness) * humBarIntensity;
    
    finalColor.rgb += humBar * humbarColor;
    
    // Exposure
    float exposure = 2.0f;
    finalColor *= exposure;
    
    // Contrast
    float contrastFactor = 1.5f;
    finalColor.rgb = (finalColor.rgb - 0.5f) * contrastFactor + 0.5f;
    
    return finalColor;
}