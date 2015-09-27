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
//enable the shader, and all its attributes
void GLProgram::use()
{
	glUseProgram(m_programID);
	//enable all the attributes we added with addAttribute
	for (int i = 0; i < m_numAttribs; i++) 
	{
		glEnableVertexAttribArray(i);
	}
}

//disable the shader
void GLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttribs; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLProgram::addAttribute(const char* attribName, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	GLint positionAttrib = glGetAttribLocation(m_programID, attribName);
	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, size, type, normalized, stride, pointer);
	m_numAttribs++;
}

void GLProgram::uploadUnifromMatrix(char* name, int num, glm::mat4 &mat, GLboolean transpose)
{
	const GLint uniLoc = getUniformLocation(name);
	const GLfloat* value = glm::value_ptr(mat);
	glUniformMatrix4fv(uniLoc, num, transpose ,value);
}