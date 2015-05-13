#version 330                                                        

varying vec3 vVertexPosition;
out vec3 FragColor;

void main()                                                                         
{     
    FragColor = vVertexPosition;                                                                              
}