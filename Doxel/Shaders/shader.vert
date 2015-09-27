#version 330 core
 
in vec3 position;
in vec4 vertexColor;

uniform mat4 mvp;

out vec4 color;
void main ()
{
	color = vertexColor;
	gl_Position = mvp * vec4(position.xyz, 1.0);
}