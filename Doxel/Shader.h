#pragma once
#include <gl\glew.h>
class Shader
{
public:
	Shader();

	~Shader();
	
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	GLuint LoadShadersFromSource(const char* vertexSource, const char* fragmentSource);
};

