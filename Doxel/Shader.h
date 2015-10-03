#pragma once
#include <gl\glew.h>
class Shader
{
public:
	Shader();

	~Shader();
	/*
	loads the shaders from a path
	*/
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	/*
	loads the shaders from a source.
	*/
	GLuint LoadShadersFromSource(const char* vertexSource, const char* fragmentSource);
};

