#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 Position;                                             
layout (location = 1) in vec2 TexCoord;                                             
layout (location = 2) in vec3 Normal;                                               
                                                                                    
uniform mat4 gWVP;
uniform mat4 gWorld;
uniform mat4 gModelViewMatrix;
uniform float fogDensity;
                                                                                    
out vec2 TexCoord0;                                                                 
out vec3 Normal0;        
out vec3 WorldPos0; 
out float fogFactor;
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = gWVP * vec4(Position, 1.0); 

	const float LOG2 = 1.442695;
	vec4 eyeSpacePos = gModelViewMatrix * vec4(Position, 1.0);
	float fogFragCoord = abs(eyeSpacePos.z/eyeSpacePos.w); 
	fogFactor = exp(-pow(fogDensity * fogFragCoord, 2.0));
	fogFactor = 1 - clamp(fogFactor, 0.0, 1.0);
	                                     
    TexCoord0   = TexCoord;                                                         
    Normal0 = (gWorld * vec4(Normal, 0.0)).xyz;       
	WorldPos0 = (gWorld * vec4(Position, 1.0)).xyz;
}