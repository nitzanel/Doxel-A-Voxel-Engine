#include "DebugRenderer.h"


DebugRenderer::DebugRenderer()
{
}


DebugRenderer::~DebugRenderer()
{
}

void DebugRenderer::createRenderBatches()
{
	if (m_polygons.empty())
	{
		Debug_Log("m_polygons is empty. Try to draw something.");
		return;
	}
	m_vertecies.reserve(m_numVertecies);
	m_indecies.reserve(m_polygons.size() * NUM_OF_VERTECIES_IN_LINED_ARC);
	uint ci = 0; /// current index.
	uint cv = 0; /// current vertex.
	uint dv = 0; // delta vertecies :D
	for (uint cp /*current polygon*/ = 0; cp < m_polygons.size(); cp++)
	{
		uint currentPolygonVerts = m_polygons[cp].vertecies.size();
		dv = currentPolygonVerts - NUM_OF_VERTECIES_IN_AN_ARC;
		// fill the vetecies vector with vetecies from the polygon.

		for (uint i = 0; i < currentPolygonVerts; i++)
		{
			m_vertecies[cv++] = m_polygons[cp].vertecies[i];
		}
		m_indecies[ci + 0] = cv - currentPolygonVerts + 0;
		m_indecies[ci + 1] = cv - currentPolygonVerts + 1;
		m_indecies[ci + 3] = cv - currentPolygonVerts + 0;
		m_indecies[ci + 2] = cv - currentPolygonVerts + 2;
		m_indecies[ci + 4] = cv - currentPolygonVerts + 1;
		m_indecies[ci + 5] = cv - currentPolygonVerts + 3;	
		m_indecies[ci + 6] = cv - currentPolygonVerts + 2;
		m_indecies[ci + 7] = cv - currentPolygonVerts + 3;
		
		m_indecies[ci + 8] = cv - currentPolygonVerts + 0;
		m_indecies[ci + 9] = cv - currentPolygonVerts + 4;
		m_indecies[ci + 10] = cv - currentPolygonVerts + 1;
		m_indecies[ci + 11] = cv - currentPolygonVerts + 5;
		m_indecies[ci + 12] = cv - currentPolygonVerts + 2;
		m_indecies[ci + 13] = cv - currentPolygonVerts + 6;
		m_indecies[ci + 14] = cv - currentPolygonVerts + 3;
		m_indecies[ci + 15] = cv - currentPolygonVerts + 7;
		
		m_indecies[ci + 16] = cv - currentPolygonVerts + 4 + dv;
		m_indecies[ci + 17] = cv - currentPolygonVerts + 5 + dv;
		m_indecies[ci + 18] = cv - currentPolygonVerts + 4 + dv;
		m_indecies[ci + 19] = cv - currentPolygonVerts + 6 + dv;
		m_indecies[ci + 20] = cv - currentPolygonVerts + 5 + dv;
		m_indecies[ci + 21] = cv - currentPolygonVerts + 7 + dv;
		m_indecies[ci + 22] = cv - currentPolygonVerts + 6 + dv;
		m_indecies[ci + 23] = cv - currentPolygonVerts + 7 + dv;

		ci += 24;
		m_numIndecies += 24;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertecies.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertecies.size() * sizeof(Vertex), m_vertecies.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indecies.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indecies.size() * sizeof(GLuint), m_indecies.data());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_numElements = m_indecies.size();
	m_indecies.clear();
	m_vertecies.clear();


}