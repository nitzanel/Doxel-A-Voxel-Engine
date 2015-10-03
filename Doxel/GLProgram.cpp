#include "GLProgram.h"
#include <glm\gtc\type_ptr.hpp>

GLProgram::GLProgram()
{
}


GLProgram::~GLProgram()
{
}

void GLProgram::loadShaders(const char* vertexPath, const char* fragmentPath)
{
	m_programID = m_shaders.LoadShaders(vertexPath, fragmentPath);
}
void GLProgram::loadShadersFromSource(const char* vertexSource, const char* fragmentSource)
{
	m_programID = m_shaders.LoadShadersFromSource(vertexSource, fragmentSource);
}

void GLProgram::uploadUniformMatrix(char* name, int num, glm::mat4 &mat, GLboolean transpose)
{
	glUseProgram(m_programID);
	const GLint uniLoc = getUniformLocation(name);
	const GLfloat* value = glm::value_ptr(mat);
	glUniformMatrix4fv(uniLoc, num, transpose ,value);
}
void GLProgram::uploadUniformVector3(char* name, int num, glm::vec3 &uni)
{
	const GLint uniLoc = getUniformLocation(name);
	const GLfloat* value = glm::value_ptr(uni);
	glUniform3fv(uniLoc, 1, value);
}