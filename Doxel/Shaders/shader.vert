#version 330 core
 
in vec3 position; // the vertex position.
in vec4 vertexColor; // the vertex color.
in vec4 normalVec; // the vertex normal.

uniform mat4 mvp; // the projection * view * model matrix.
uniform mat4 m; // the model matrix.
uniform mat4 v; // the view matrix.
uniform vec3 lightPosition_worldSpace; // the position of the light object in world space coordinations.

out vec4 color; // the color that passes to the fragment shader.
out vec3 normal_cameraSpace; // the vertex normal in camera space.
out vec3 lightDirection_cameraSpace; // the direction of the light in camera space.

void main ()
{
	vec3 normalNormalized = normalize(normalVec.xyz);
	color = vertexColor;
	gl_Position = mvp * vec4(position.xyz, 1.0);

	//vector that goes from the vertex to the camera, in camera space.
	// in the camera space, the camera is at (0,0,0).
	vec3 vertexPosition_cameraSpace = (v * m * vec4(position,1)).xyz;
	vec3 eyeDirection_cameraSpace = vec3(0,0,0) - vertexPosition_cameraSpace;
	
	//vector that goes from the vertex to the light, in camera space. m is omitted because its identity
	vec3 lightPosition_cameraSpace = (v * vec4(lightPosition_worldSpace,1)).xyz;
	lightDirection_cameraSpace = lightPosition_cameraSpace + eyeDirection_cameraSpace;
	// Normal of the the vertex, in camera space
	normal_cameraSpace = (v * m * vec4(normalNormalized,0)).xyz;

}