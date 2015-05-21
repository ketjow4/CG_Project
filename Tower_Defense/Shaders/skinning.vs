#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 Position;                                             
layout (location = 1) in vec2 TexCoord;                                             
layout (location = 2) in vec3 Normal;                                               
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

out vec2 TexCoord0;
out vec3 Normal0;                                                                   
out vec3 WorldPos0;       
out vec4 LightSpacePos;
out float fogFactor;                                                           

const int MAX_BONES = 100;

uniform mat4 gWVP;
uniform mat4 gWV;
uniform mat4 gWorld;
uniform mat4 gBones[MAX_BONES];
uniform mat4 gLightWVP; 
uniform float fogDensity;

void main()
{       
    mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
    BoneTransform     += gBones[BoneIDs[1]] * Weights[1];
    BoneTransform     += gBones[BoneIDs[2]] * Weights[2];
    BoneTransform     += gBones[BoneIDs[3]] * Weights[3];

    vec4 PosL    = BoneTransform * vec4(Position, 1.0);
    gl_Position  = gWVP * PosL;
    TexCoord0    = TexCoord;
    vec4 NormalL = BoneTransform * vec4(Normal, 0.0);
    Normal0      = (gWorld * NormalL).xyz;
    WorldPos0    = (gWorld * PosL).xyz;                 
	LightSpacePos = gLightWVP * vec4(Position, 1.0); 
	
	const float LOG2 = 1.442695;
	vec4 eyeSpacePos = gWV * PosL;
	float fogFragCoord = abs(eyeSpacePos.z/eyeSpacePos.w); 
	fogFactor = exp(-pow(fogDensity * fogFragCoord, 2.0));
	fogFactor = 1 - clamp(fogFactor, 0.0, 1.0); 		
}

