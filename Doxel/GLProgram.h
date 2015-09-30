#pragma once
#include "Shader.h"
#include <glm\glm.hpp>
class GLProgram
{
public:
	GLProgram();
	~GLProgram();

	void loadShaders(const char* vertexPath, const char* fragmentPath);
	void loadShadersFromSource(const char* vertexSource, const char* fragmentSource);
	void use();
	void unuse();

	void addAttribute(const char* attribName, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

	void deleteProgram() {if(m_programID) glDeleteProgram(m_programID); }
	GLuint getID() { return m_programID; }
	
	void uploadUniformMatrix(char* name, int num, glm::mat4 &mat, GLboolean transpose);
	GLint getUniformLocation(char* name) { return glGetUniformLocation(m_programID, name); }
	void uploadUniformVector3(char* name, int num, glm::vec3 &uni);


private:
	GLuint m_programID;
	Shader m_shaders;

	int m_numAttribs = 0;
};

