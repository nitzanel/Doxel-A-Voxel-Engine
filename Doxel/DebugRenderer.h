#pragma once

#include "GLProgram.h"
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>
class DebugRenderer
{
public:
	DebugRenderer();
	~DebugRenderer();

	void init();
	void end();
	void drawCube(const glm::vec3& position,const glm::vec3& scale, const Color8 color);
	void drawSphere(const glm::vec3& center, const Color8 color, float radius);
	void render( glm::mat4& projectionMatrix,  glm::mat4& viewMatrix, float lineWidth);
	void dispose();

	struct DebugVertex{
		glm::vec3 position; 
		Color8 color;
	};

private:
	GLProgram m_program;
	std::vector <DebugVertex> m_verts;
	std::vector<GLuint> m_indices;
	GLuint m_vbo = 0, m_vao = 0, m_ibo = 0;

	DebugVertex m_cubeVerts[8];
	int m_numElements = 0;
};

