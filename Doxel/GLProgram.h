/*
This file contains the GLProgram class.
*/
#pragma once
#include "Shader.h"
#include <glm\glm.hpp>
/*
The GLProgram class, used for interactions with the shaders.
*/
class GLProgram
{
public:
	/*
	Create a GLProgram object.
	EMPTY.
	*/
	GLProgram();
	/*
	Destroy a GLProgram object.
	EMPTY.
	*/
	~GLProgram();
	/*
	Load the shaders from a path and sends them to loadShadersFromSource.
	Input:
		-const char* vertexPath - the path file of the vertex shader.
		-const char* fragmentPath - the path file of the fragment shader.
	*/
	void loadShaders(const char* vertexPath, const char* fragmentPath);
	/*
	Load the shaders from a source.
	Input: 
		-const char* vertexSource - the source of the vertex shader (the code).
		-const char* fragmentSource - the source of the fragment shader (the code).
	*/
	void loadShadersFromSource(const char* vertexSource, const char* fragmentSource);
	/*
	Deletes the program.
	Call after the game loop.
	*/
	void deleteProgram() {if(m_programID) glDeleteProgram(m_programID); }
	/*
	Get the program id as a GLuint.
	*/
	GLuint getID() { return m_programID; }
	/*
	Upload a uniform matrix to the shader.
	Input:
		-char* name - the name of the uniform.
		-int num - the number of uniforms to send. should be 1 if not an array of matrixes.
		-glm::mat4 &mat - the matrix you want to upload.
		-GLboolean transpose - should matrix be tranposed? GL_TRUE for yes GL_FALSE for no.
	*/
	void uploadUniformMatrix(char* name, int num, glm::mat4 &mat, GLboolean transpose);
	/*
	Returns a uniform location as a GLint.
	*/
	GLint getUniformLocation(char* name) { return glGetUniformLocation(m_programID, name); }
	/*
	upload a unirom vector 3.
	-char* name - the name of the uniform.
	-int num - the number of uniforms to send. should be 1 if not an array of vectors.
	-glm::vec3 &uni - the uniform vector you want to upload.
	*/
	void uploadUniformVector3(char* name, int num, glm::vec3 &uni);
	void uploadUniformFloat(char* name, int num, float val);
	void uploadUniformVector4(char* name, int num , glm::vec4 &val);
private:
	GLuint m_programID;
	Shader m_shaders;

	int m_numAttribs = 0;
};

