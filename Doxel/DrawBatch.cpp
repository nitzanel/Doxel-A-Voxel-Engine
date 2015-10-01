#include "DrawBatch.h"


DrawBatch::DrawBatch() : m_vbo(0), m_vao(0)
{

}


DrawBatch::~DrawBatch()
{

}


void DrawBatch::init(Camera3D *camera)
{
	createVertexArray();

	m_camera = camera;
}
void DrawBatch::start()
{	
	m_renderBatches.clear();

	m_glyphs.clear();

	m_camera->getFrustum();
}
void DrawBatch::end()
{
	createRenderBatches();
}
void DrawBatch::draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[8], bool overrideFrustum/* = false*/)
{
	if (overrideFrustum)
	{
		m_glyphs.emplace_back(position, scale, color);
	}
	else
	{
	/*	if (lastBatchChecked)
		{
			if(lastBatchInFrustum)m_glyphs.emplace_back(position, scale, color);
			lastBatchChecked = false;
			return;
		}*/

		if (m_camera->inFrame(position))
		{
			m_glyphs.emplace_back(position, scale, color);
		//	if(lastBatchChecked =false)lastBatchChecked = true;
		//	lastBatchInFrustum = true;
	/*	}
		else
		{
	//		if (lastBatchChecked = false)lastBatchChecked = true;
	//		lastBatchInFrustum = false;*/
		}

	}
}
void DrawBatch::draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 &color, bool overrideFrustum/* = false*/)
{
	if (overrideFrustum)
	{
		m_glyphs.emplace_back(position, scale, color);
	}
	else
	{
		if (m_camera->inFrame(position))
			m_glyphs.emplace_back(position, scale, color);
	}

}


void DrawBatch::renderBatch()
{
	glBindVertexArray(m_vao);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	for (unsigned int i = 0; i < m_renderBatches.size(); i++)
	{
		// bind texture if there is -> there will never be but whatever
	//	glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertecies);
		glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_INT, (void*)0);
	}
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void DrawBatch::createRenderBatches()
{
	std::vector <Vertex> vertecies;
	vertecies.resize(m_glyphs.size() * 8);
	m_indecies.resize(m_glyphs.size() * 36);
	unsigned int ci = 0; /// current indecie
	if (m_glyphs.empty())
	{
		return;
	}
	int offset = 0;// use offset for texture new batches otherwise not needed
	int cv = 0; /// current vertex
	
	m_renderBatches.emplace_back(offset, 0);

	for (unsigned int cg = 0; cg < m_glyphs.size(); cg++) // cg = current glyph
	{
		m_renderBatches.back().numVertecies += 36;	

		
		vertecies[cv++] = m_glyphs[cg].vertecies[0];
		vertecies[cv++] = m_glyphs[cg].vertecies[1];
		vertecies[cv++] = m_glyphs[cg].vertecies[2];
		vertecies[cv++] = m_glyphs[cg].vertecies[3];
		vertecies[cv++] = m_glyphs[cg].vertecies[4];
		vertecies[cv++] = m_glyphs[cg].vertecies[5];
		vertecies[cv++] = m_glyphs[cg].vertecies[6];
		vertecies[cv++] = m_glyphs[cg].vertecies[7];

		/*vertecies[cv++] = m_glyphs[cg].vertecies[0];
		vertecies[cv++] = m_glyphs[cg].vertecies[1];
		vertecies[cv++] = m_glyphs[cg].vertecies[2];
		vertecies[cv++] = m_glyphs[cg].vertecies[1];
		vertecies[cv++] = m_glyphs[cg].vertecies[2];
		vertecies[cv++] = m_glyphs[cg].vertecies[3];*/
		
		m_indecies[ci+0] = cg * 8 + 0;
		m_indecies[ci+1] = cg * 8+ 1;
		m_indecies[ci+2] = cg * 8+ 2;
		m_indecies[ci + 3] = cg * 8 + 1;
		m_indecies[ci + 4] = cg * 8 + 2;
		m_indecies[ci + 5] = cg * 8 + 3;

		m_indecies[ci + 6] = cg * 8 + 0;
		m_indecies[ci + 7] = cg * 8 + 1;
		m_indecies[ci + 8] = cg * 8 + 4;
		m_indecies[ci + 9] = cg * 8 + 1;
		m_indecies[ci + 10] = cg * 8 + 4;
		m_indecies[ci + 11] = cg * 8 + 5;

		m_indecies[ci + 12] = cg * 8 + 1;
		m_indecies[ci + 13] = cg * 8 + 3;
		m_indecies[ci + 14] = cg * 8 + 5;
		m_indecies[ci + 15] = cg * 8 + 3;
		m_indecies[ci + 16] = cg * 8 + 5;
		m_indecies[ci + 17] = cg * 8 + 7;

		m_indecies[ci + 18] = cg * 8 + 0;
		m_indecies[ci + 19] = cg * 8 + 2;
		m_indecies[ci + 20] = cg * 8 + 4;
		m_indecies[ci + 21] = cg * 8 + 2;
		m_indecies[ci + 22] = cg * 8 + 4;
		m_indecies[ci + 23] = cg * 8 + 6;

		m_indecies[ci + 24] = cg * 8 + 2;
		m_indecies[ci + 25] = cg * 8 + 3;
		m_indecies[ci + 26] = cg * 8 + 6;
		m_indecies[ci + 27] = cg * 8 + 3;
		m_indecies[ci + 28] = cg * 8 + 6;
		m_indecies[ci + 29] = cg * 8 + 7;

		m_indecies[ci + 30] = cg * 8 + 4;
		m_indecies[ci + 31] = cg * 8 + 5;
		m_indecies[ci + 32] = cg * 8 + 6;
		m_indecies[ci + 33] = cg * 8 + 5;
		m_indecies[ci + 34] = cg * 8 + 6;
		m_indecies[ci + 35] = cg * 8 + 7;

	/*	vertecies[cv++] = m_glyphs[cg].vertecies[0];
		vertecies[cv++] = m_glyphs[cg].vertecies[1];
		vertecies[cv++] = m_glyphs[cg].vertecies[4];
		vertecies[cv++] = m_glyphs[cg].vertecies[1];
		vertecies[cv++] = m_glyphs[cg].vertecies[4];
		vertecies[cv++] = m_glyphs[cg].vertecies[5];
	

		vertecies[cv++] = m_glyphs[cg].vertecies[1];
		vertecies[cv++] = m_glyphs[cg].vertecies[3];
		vertecies[cv++] = m_glyphs[cg].vertecies[5];
		vertecies[cv++] = m_glyphs[cg].vertecies[3];
		vertecies[cv++] = m_glyphs[cg].vertecies[5];
		vertecies[cv++] = m_glyphs[cg].vertecies[7];
	
		vertecies[cv++] = m_glyphs[cg].vertecies[0];
		vertecies[cv++] = m_glyphs[cg].vertecies[2];
		vertecies[cv++] = m_glyphs[cg].vertecies[4];	
		vertecies[cv++] = m_glyphs[cg].vertecies[2];
		vertecies[cv++] = m_glyphs[cg].vertecies[4];
		vertecies[cv++] = m_glyphs[cg].vertecies[6];
	
		vertecies[cv++] = m_glyphs[cg].vertecies[2];
		vertecies[cv++] = m_glyphs[cg].vertecies[3];
		vertecies[cv++] = m_glyphs[cg].vertecies[6];	
		vertecies[cv++] = m_glyphs[cg].vertecies[3];
		vertecies[cv++] = m_glyphs[cg].vertecies[6];
		vertecies[cv++] = m_glyphs[cg].vertecies[7];
	
		vertecies[cv++] = m_glyphs[cg].vertecies[4];
		vertecies[cv++] = m_glyphs[cg].vertecies[5];
		vertecies[cv++] = m_glyphs[cg].vertecies[6];	
		vertecies[cv++] = m_glyphs[cg].vertecies[5];
		vertecies[cv++] = m_glyphs[cg].vertecies[6];
		vertecies[cv++] = m_glyphs[cg].vertecies[7];*/
		ci +=36;
		offset += 36;
	}	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	// orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	// upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertecies.size() * sizeof(Vertex), vertecies.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indecies.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indecies.size() * sizeof(GLuint), m_indecies.data());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	m_numElements = m_indecies.size();
	m_indecies.clear(); 

}

void DrawBatch::createVertexArray()
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
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glBindVertexArray(0);
}

void DrawBatch::dispose()
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