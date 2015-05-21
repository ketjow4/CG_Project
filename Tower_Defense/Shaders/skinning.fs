#version 330

struct VSOutput
{
    vec2 TexCoord;
    vec3 Normal;
    vec3 WorldPos;
};

struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

struct Attenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct PointLight
{
    BaseLight Base;
    vec3 Position;
    Attenuation Atten;
};

struct SpotLight
{
    PointLight Base;
    vec3 Direction;
    float Cutoff;
};

const int MAX_POINT_LIGHTS = 2;
const int MAX_SPOT_LIGHTS = 2;

in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;
in float fogFactor; 
in vec4 LightSpacePos; 

uniform int gNumPointLights;
uniform int gNumSpotLights;

uniform float gMatSpecularIntensity;
uniform float gSpecularPower;

uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLights[MAX_POINT_LIGHTS];
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS];
uniform sampler2D gColorMap;
uniform vec3 gEyeWorldPos;
uniform sampler2D gShadowMap; 

uniform vec4 fogColor; 

out vec4 FragColor;

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, VSOutput In, float ShadowFactor);
vec4 CalcDirectionalLight(VSOutput In);
vec4 CalcPointLight(PointLight l, VSOutput In, vec4 LightSpacePos);
vec4 CalcSpotLight(SpotLight l, VSOutput In, vec4 LightSpacePos);
float CalcShadowFactor(vec4 LightSpacePos);

void main()
{
    VSOutput In;
    In.TexCoord = TexCoord0;
    In.Normal = normalize(Normal0);
    In.WorldPos = WorldPos0;

    vec4 TotalLight = CalcDirectionalLight(In);

    for (int i = 0 ; i < gNumPointLights ; i++)
        TotalLight += CalcPointLight(gPointLights[i], In, LightSpacePos);

    for (int i = 0 ; i < gNumSpotLights ; i++)
        TotalLight += CalcSpotLight(gSpotLights[i], In, LightSpacePos);

    vec4 finalColor = texture(gColorMap, In.TexCoord.xy); //* TotalLight;
    vec4 foggedColor = mix(finalColor, fogColor, fogFactor);
	FragColor = foggedColor;
}

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, VSOutput In, float ShadowFactor)
{
    vec4 AmbientColor = vec4(Light.Color, 1.0) * Light.AmbientIntensity;
    float DiffuseFactor = dot(In.Normal, -LightDirection);

    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0.0)
    {
        DiffuseColor = vec4(Light.Color, 1.0) * Light.DiffuseIntensity * DiffuseFactor;

        vec3 VertexToEye = normalize(gEyeWorldPos - In.WorldPos);
        vec3 LightReflect = normalize(reflect(LightDirection, In.Normal));
        float SpecularFactor = dot(VertexToEye, LightReflect);
        SpecularFactor = pow(SpecularFactor, gSpecularPower);
        if (SpecularFactor > 0.0)
            SpecularColor = vec4(Light.Color, 1.0) * gMatSpecularIntensity * SpecularFactor;
    }

    return (AmbientColor +  ShadowFactor * (DiffuseColor + SpecularColor));
}

vec4 CalcDirectionalLight(VSOutput In)
{
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, In, 1.0);
}

vec4 CalcPointLight(PointLight l, VSOutput In, vec4 LightSpacePos)
{
    vec3 LightDirection = In.WorldPos - l.Position;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);
	float ShadowFactor = CalcShadowFactor(LightSpacePos);

    vec4 Color = CalcLightInternal(l.Base, LightDirection, In, ShadowFactor);
    float Attenuation = l.Atten.Constant +
    l.Atten.Linear * Distance +
    l.Atten.Exp * Distance * Distance;

    return Color / Attenuation;
}

vec4 CalcSpotLight(SpotLight l, VSOutput In, vec4 LightSpacePos)
{
    vec3 LightToPixel = normalize(In.WorldPos - l.Base.Position);
    float SpotFactor = dot(LightToPixel, l.Direction);

    //if (SpotFactor > l.Cutoff)
    //{
        vec4 Color = CalcPointLight(l.Base, In, LightSpacePos);
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));
   // }
   // return vec4(0,0,0,0);
}


float CalcShadowFactor(vec4 LightSpacePos)                                                  
{                                                                                           
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;                                  
    vec2 UVCoords;                                                                          
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;                                                  
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;                                                  
    float z = 0.5 * ProjCoords.z + 0.5;                                                     
    float Depth = texture(gShadowMap, UVCoords).x;                                          
    if (Depth < z + 0.00001)                                                                 
        return 0.0;                                                                         
    else                                                                                    
        return 1.0;                                                                         
}   
