#include "DebugRenderer.h"

namespace{
	const char* VERT_SRC = R"(#version 330 core

in vec3 vertexPosition;
in vec4 vertexColor;

out vec3 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 P;
uniform mat4 V;



void main()
{
	gl_Position = P * V * vec4(vertexPosition, 1.0);
	fragmentPosition = vertexPosition;
	fragmentColor = vertexColor;
})";

	const char* FRAG_SRC = R"(#version 330 core

in vec3 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

void main()
{
	color= fragmentColor;
})";
}
DebugRenderer::DebugRenderer()
{

}


DebugRenderer::~DebugRenderer()
{
	dispose();
}

void DebugRenderer::init()
{
	// Shader init
	m_program.loadShadersFromSource(VERT_SRC, FRAG_SRC);
	m_program.addAttribute("vertexPosition", 3,GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
	m_program.addAttribute("vertexColor", 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

	// Set up buffers
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	//  TODO VERTEX ATRRIB POINTERS
	m_program.use();
	glBindVertexArray(0);


}
void DebugRenderer::end()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	// orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
	// upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_verts.size() * sizeof(DebugVertex), m_verts.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	// orphan the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
	// upload the data
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_numElements = m_indices.size();
	m_indices.clear();
	m_verts.clear();
}
void DebugRenderer::drawCube(const glm::vec3& position, const glm::vec3& scale, const Color8 color)
{
	int j = m_verts.size();
	m_verts.resize(m_verts.size() + 8);

	for (int i = 0; i < 8; i++)
	{
		m_cubeVerts[i].color = color;
	}
	// TODO - DIFFERENT COLORS , maybe Color8[8]
	m_cubeVerts[0].position = glm::vec3(position.x, position.y, position.z);
	m_cubeVerts[1].position = glm::vec3(position.x + scale.x, position.y, position.z);
	m_cubeVerts[2].position = glm::vec3(position.x, position.y + scale.y, position.z);
	m_cubeVerts[3].position = glm::vec3(position.x + scale.x, position.y + scale.y, position.z);
	m_cubeVerts[4].position = glm::vec3(position.x, position.y, position.z + scale.z);
	m_cubeVerts[5].position = glm::vec3(position.x + scale.x, position.y, position.z + scale.z);
	m_cubeVerts[6].position = glm::vec3(position.x, position.y + scale.y, position.z + scale.z);
	m_cubeVerts[7].position = glm::vec3(position.x + scale.x, position.y + scale.y, position.z + scale.z);


	for (int k = 0; k < 8; k++)
	{
		m_verts[j + k] = m_cubeVerts[k];
	}
	m_indices.reserve(m_indices.size() + 24);
	
	m_indices.push_back(j + 0);
	m_indices.push_back(j + 1);
	m_indices.push_back(j + 1);
	m_indices.push_back(j + 3);
	m_indices.push_back(j + 2);
	m_indices.push_back(j + 3);
	m_indices.push_back(j + 0);
	m_indices.push_back(j + 2);


	m_indices.push_back(j + 0);
	m_indices.push_back(j + 4);
	m_indices.push_back(j + 1);
	m_indices.push_back(j + 5);
	m_indices.push_back(j + 2);
	m_indices.push_back(j + 6);
	m_indices.push_back(j + 3);
	m_indices.push_back(j + 7);
	

	m_indices.push_back(j + 4);
	m_indices.push_back(j + 5);
	m_indices.push_back(j + 4);
	m_indices.push_back(j + 6);
	m_indices.push_back(j + 5);
	m_indices.push_back(j + 7);
	m_indices.push_back(j + 6);
	m_indices.push_back(j + 7);

	/* for triangles if do
	m_indices.push_back(j + 0);
	m_indices.push_back(j + 1);
	m_indices.push_back(j + 2);

	m_indices.push_back(j + 0);
	m_indices.push_back(j + 1);
	m_indices.push_back(j + 4);

	m_indices.push_back(j + 1);
	m_indices.push_back(j + 4);
	m_indices.push_back(j + 5);

	m_indices.push_back(j + 1);
	m_indices.push_back(j + 3);
	m_indices.push_back(j + 5);
	
	m_indices.push_back(j + 3);
	m_indices.push_back(j + 5);
	m_indices.push_back(j + 7);
	
	m_indices.push_back(j + 0);
	m_indices.push_back(j + 2);
	m_indices.push_back(j + 4);
	
	m_indices.push_back(j + 2);
	m_indices.push_back(j + 4);
	m_indices.push_back(j + 6);

	m_indices.push_back(j + 2);
	m_indices.push_back(j + 3);
	m_indices.push_back(j + 6);

	m_indices.push_back(j + 3);
	m_indices.push_back(j + 6);
	m_indices.push_back(j + 7);

	m_indices.push_back(j + 4);
	m_indices.push_back(j + 5);
	m_indices.push_back(j + 6);

	m_indices.push_back(j + 5);
	m_indices.push_back(j + 6);
	m_indices.push_back(j + 7);

	*/
};
void DebugRenderer::drawSphere(const glm::vec3& center, const Color8 color, float radius)
{
	// TO DO
/*	static const int NUM_VERTS = 100;
	int start = m_verts.size();
	for (int i = 0; i < NUM_VERTS; i++)
	{

	}
	*/
}
void DebugRenderer::render( glm::mat4& projectionMatrix,  glm::mat4& viewMatrix, float lineWidth)
{
	m_program.use();
	m_program.uploadUnifromMatrix("P", 1, projectionMatrix, GL_FALSE);
	m_program.uploadUnifromMatrix("V", 1, viewMatrix, GL_FALSE);

	glLineWidth(lineWidth);
	glBindVertexArray(m_vao);
	glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	m_program.unuse();
}
void DebugRenderer::dispose()
{
	if (m_vao)
	{
		glDeleteVertexArrays(1, &m_vao);
	}
	if (m_vbo)
	{
		glDeleteBuffers(1, &m_vbo);
	}
	if (m_ibo)
	{
		glDeleteBuffers(1, &m_ibo);
	}
	m_program.deleteProgram();
}