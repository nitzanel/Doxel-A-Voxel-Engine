#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"
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

		/*glm::vec3 normals[8][3];
		normals[0][0] = glm::normalize(glm::cross(vertecies[1].positionToGlm() - vertecies[0].positionToGlm(),vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normals[0][1] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[1].positionToGlm() - vertecies[0].positionToGlm()));
		normals[0][2] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm())); 
		normals[1][0] = normals[0][0];
		normals[1][1] = normals[0][1];
		normals[1][2] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[1].positionToGlm(), vertecies[5].positionToGlm() - vertecies[1].positionToGlm())); 
		normals[2][0] = normals[0][0];
		normals[2][1] = normals[0][2];
		normals[2][2] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[2].positionToGlm(), vertecies[6].positionToGlm() - vertecies[2].positionToGlm()));
		normals[3][0] = normals[1][0];
		normals[3][1] = normals[1][2];
		normals[3][2] = normals[2][2];
		normals[4][0] = normals[1][1];
		normals[4][1] = normals[2][1];
		normals[4][2] = glm::normalize(glm::cross(vertecies[5].positionToGlm() - vertecies[4].positionToGlm(), vertecies[6].positionToGlm() - vertecies[4].positionToGlm()));
		normals[5][0] = normals[1][1];
		normals[5][1] = normals[1][2];
		normals[5][2] = normals[4][2];
		normals[6][0] = normals[2][1];
		normals[6][1] = normals[2][2];
		normals[6][2] = normals[4][2];
		normals[7][0] = normals[1][2];
		normals[7][1] = normals[2][2];
		normals[7][2] = normals[4][2];*/

		glm::vec3 normalVecs[6];
		normalVecs[0] = glm::normalize(glm::cross(vertecies[1].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[1] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[1].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[2] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[3] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[1].positionToGlm(), vertecies[5].positionToGlm() - vertecies[1].positionToGlm()));
		normalVecs[4] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[2].positionToGlm(), vertecies[6].positionToGlm() - vertecies[2].positionToGlm()));
		normalVecs[5] = glm::normalize(glm::cross(vertecies[5].positionToGlm() - vertecies[4].positionToGlm(), vertecies[6].positionToGlm() - vertecies[4].positionToGlm()));

		vertecies[0].setNormal(glm::normalize(normalVecs[0] + normalVecs[1] + normalVecs[2]));
		vertecies[1].setNormal(glm::normalize(normalVecs[0] + normalVecs[1] + normalVecs[3]));
		vertecies[2].setNormal(glm::normalize(normalVecs[0] + normalVecs[2] + normalVecs[4]));
		vertecies[3].setNormal(glm::normalize(normalVecs[0] + normalVecs[2] + normalVecs[3]));
		vertecies[4].setNormal(glm::normalize(normalVecs[0] + normalVecs[2] + normalVecs[5]));
		vertecies[5].setNormal(glm::normalize(normalVecs[0] + normalVecs[3] + normalVecs[5]));
		vertecies[6].setNormal(glm::normalize(normalVecs[2] + normalVecs[4] + normalVecs[5]));
		vertecies[7].setNormal(glm::normalize(normalVecs[3] + normalVecs[4] + normalVecs[5]));


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

		glm::vec3 normalVecs[6];
		normalVecs[0] = glm::normalize(glm::cross(vertecies[1].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[1] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[1].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[2] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[3] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[1].positionToGlm(), vertecies[5].positionToGlm() - vertecies[1].positionToGlm()));
		normalVecs[4] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[2].positionToGlm(), vertecies[6].positionToGlm() - vertecies[2].positionToGlm()));
		normalVecs[5] = glm::normalize(glm::cross(vertecies[5].positionToGlm() - vertecies[4].positionToGlm(), vertecies[6].positionToGlm() - vertecies[4].positionToGlm()));

		vertecies[0].setNormal(glm::normalize(normalVecs[0] + normalVecs[1] + normalVecs[2]));
		vertecies[1].setNormal(glm::normalize(normalVecs[0] + normalVecs[1] + normalVecs[3]));
		vertecies[2].setNormal(glm::normalize(normalVecs[0] + normalVecs[2] + normalVecs[4]));
		vertecies[3].setNormal(glm::normalize(normalVecs[0] + normalVecs[2] + normalVecs[3]));
		vertecies[4].setNormal(glm::normalize(normalVecs[0] + normalVecs[2] + normalVecs[5]));
		vertecies[5].setNormal(glm::normalize(normalVecs[0] + normalVecs[3] + normalVecs[5]));
		vertecies[6].setNormal(glm::normalize(normalVecs[2] + normalVecs[4] + normalVecs[5]));
		vertecies[7].setNormal(glm::normalize(normalVecs[3] + normalVecs[4] + normalVecs[5]));
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
																							
