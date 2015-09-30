#version 330 core

in vec4 color;
in vec3 normal_cameraspace;
in vec3 lightDirection_cameraspace;

out vec4 colorOut;
 
void main()
{
	vec3 n = normalize(normal_cameraspace);
	vec3 l = normalize(lightDirection_cameraspace);

	float cosTheta = clamp(dot(n,l), 0,1);

    colorOut = vec4(color) * cosTheta;
}