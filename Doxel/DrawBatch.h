#pragma once

#include <GL\glew.h>
#include "Vertex.h"
#include <vector>
#include "Camera3D.h"
class Glyph
{
public:
	Glyph() {};
	Glyph(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[8])
	{
		for (int i = 0; i < 8; i++)
		{
			vertecies[i].color = color[i];
		}

		vertecies[0].setPosition(glm::vec3(position.x, position.y, position.z));
		vertecies[1].setPosition(glm::vec3(position.x + scale.x, position.y, position.z));
		vertecies[2].setPosition(glm::vec3(position.x, position.y + scale.y, position.z));
		vertecies[3].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z));
		vertecies[4].setPosition(glm::vec3(position.x, position.y, position.z + scale.z));
		vertecies[5].setPosition(glm::vec3(position.x + scale.x, position.y, position.z + scale.z));
		vertecies[6].setPosition(glm::vec3(position.x, position.y + scale.y, position.z + scale.z));
		vertecies[7].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z + scale.z));

	};
	Glyph(const glm::vec3 &position, const glm::vec3 &scale, Color8 color)
	{
		for (int i = 0; i < 8; i++)
		{
			vertecies[i].color = color;
		}
		// TODO - DIFFERENT COLORS , maybe Color8[8]
		vertecies[0].setPosition(glm::vec3(position.x, position.y, position.z));
		vertecies[1].setPosition(glm::vec3(position.x + scale.x, position.y, position.z));
		vertecies[2].setPosition(glm::vec3(position.x, position.y + scale.y, position.z));
		vertecies[3].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z));
		vertecies[4].setPosition(glm::vec3(position.x, position.y, position.z + scale.z));
		vertecies[5].setPosition(glm::vec3(position.x + scale.x, position.y, position.z + scale.z));
		vertecies[6].setPosition(glm::vec3(position.x, position.y + scale.y, position.z + scale.z));
		vertecies[7].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z + scale.z));
	};

		Vertex vertecies[8];
private:
};

class RenderBatch
{
public:
	RenderBatch(GLuint Offset, GLuint Numvertecies) : offset(Offset), numVertecies(Numvertecies)
	{
		//Empty
	}
	GLuint offset;
	GLuint numVertecies;
	
};

class DrawBatch
{
public:
	DrawBatch();
	~DrawBatch();

	void init(Camera3D *camera);

	void start();
	void end();

	void draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[8], bool overrideFrustum = false);
	void draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 &color, bool overrideFrustum = false);

	void renderBatch();

	void dispose();

private:
	void createRenderBatches(); 
	void createVertexArray();

	bool lastBatchChecked;
	bool lastBatchInFrustum;

	Camera3D *m_camera;
	GLuint m_vbo, m_vao;

	std::vector<Glyph> m_glyphs;
	std::vector<RenderBatch> m_renderBatches; 

};
																							
