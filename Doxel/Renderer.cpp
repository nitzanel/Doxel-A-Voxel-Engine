#include "Renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

/*
Initialize the Renderer.
Input:
-Camera3D* camera - a pointer to the main camera being used in the game. for frustum culling.
*/
void Renderer::init(Camera3D *camera)
{
	createVertexArray();

	m_camera = camera;
}

/*
Dispose the Renderer.
*/
void Renderer::dispose()
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
}

/*
Start the rendering sequence.
*/
void Renderer::start()
{
	//m_renderBatches.clear(); turn on when renderBatches is implemented

	m_polygons.clear();

	m_camera->getFrustum();
}
/*
Ends the Rendering sequence.
*/
void Renderer::end()
{
	createRenderBatches();
}

/*
Render the batch.
*/
void Renderer::renderBatch()
{
	
	glBindVertexArray(m_vao);
	switch (m_drawType)
	{
	case LINES:
		glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, (void*)0);
		break;
	case TRIANGLES:
		glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_INT, (void*)0);
		break;
	case QUADS:
		glDrawElements(GL_QUADS, m_numElements, GL_UNSIGNED_INT, (void*)0);
		break;
	default:
		break;	
	}
	glBindVertexArray(0);
}

/*
**** Draw calls to match Polygon class ****
*/
void Renderer::draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 color)
{
	m_polygons.emplace_back(position, scale, color);
}
void Renderer::draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[2])
{
	m_polygons.emplace_back(position, scale, color);
}

void Renderer::createVertexArray()
{
	if (m_vao == 0)
	{
		glGenVertexArrays(1, &m_vao);
	}
	glBindVertexArray(m_vao); // will do all the binding stuff of gl and rest 

	if (m_vbo == 0)
	{
		glGenBuffers(1, &m_vbo);
	}
	if (m_ibo == 0)
	{
		glGenBuffers(1, &m_ibo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 4, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glBindVertexArray(0);
}
