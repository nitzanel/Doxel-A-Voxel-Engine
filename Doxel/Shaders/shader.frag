#version 330 core

in vec4 color;
in vec3 normal_cameraSpace;
in vec3 lightDirection_cameraSpace;

out vec4 colorOut;
 
void main()
{
	vec3 n = normalize(normal_cameraSpace);
	vec3 l = normalize(lightDirection_cameraSpace);
	vec4 materialAmbientColor = vec4(0.01,0.01,0.01,1) * color;
	float cosTheta = clamp(dot(n,l), 0,1);

    colorOut =  materialAmbientColor + vec4(color) * cosTheta;
}