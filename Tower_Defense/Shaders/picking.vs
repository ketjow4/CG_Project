#version 330

layout (location = 0) in vec3 Position;                                             

varying vec3 vVertexPosition;
uniform mat4 gWVP;                                                                  

void main()                                                                         
{                                                                                   
	gl_Position = gWVP * vec4(Position, 1.0); 
	vVertexPosition = Position;
}