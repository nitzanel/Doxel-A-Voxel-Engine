#version 330 core
 
in vec3 position;
in vec4 vertexColor;
in vec3 normalVec;

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform vec3 lightPosition_worldSpace;

out vec4 color;
out vec3 normal_cameraspace;
out vec3 lightDirection_cameraspace;
void main ()
{
	color = vertexColor;
	gl_Position = mvp * vec4(position.xyz, 1.0);

	// position of the vertex in world space : model * position.
	vec3 positionWorldSpace = (m * vec4(position,1)).xyz;
	
	//vector that goes from the vertex to the camera, in camera space.
	vec3 vertexPosition_cameraspace = (v * m * vec4(position,1)).xyz;
	vec3 eyeDirection_cameraspace = /*vec3(0,0,0) -*/ vertexPosition_cameraspace;
	
	//vector that goes from the vertex to the light, in camera space. m is omitted because its identity
	vec3 lightPosition_cameraspace = (v * vec4(lightPosition_worldSpace,1)).xyz;
	lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;
	// Normal of the the vertex, in camera space
	normal_cameraspace = (v * m * vec4(normalVec,0)).xyz;

}