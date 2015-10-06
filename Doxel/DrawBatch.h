/*
FILE DESCRIPTION:
This file contains the Glyph class, RenderBatch class and DrawBatch class.
*/

#pragma once
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"
#include "Camera3D.h"

/*
The number of vertecies in a glyph object.
*/
#define NUMBER_OF_VERTS_IN_GLYPH 8
/*
the number of indecies there are in a cube.
*/
#define NUMBER_OF_INDECIES_IN_A_CUBE 36
/*
the number of normal vectors in a cube. one for each face.
*/
#define NUMBER_OF_NORMALS_IN_A_CUBE 6

/*
The Glyph class, a basic wraper for Vertex class usage.
It will contain many (3 right now) constructors for setup of the vertecies.
*/
class Glyph
{
public:
	/*
	Default constructor.
	Empty.
	*/
	Glyph() {/* EMPTY */};
	/*
	Constructor.
	Input:
	-const glm::vec3 &position - the position of the cube in world coordinates (we *currently* do not use a translation matrix).
	-const glm::vec3 &scale - the scale of the cube, in x, y, and z coordiantions.
	-Color8 color[2] - color[0] the color of ground, color[1] the color of grass.
	Output:
	-Glyph - a glyph object set-up and ready to go.
	Note: the constructor will also calculate the vertecies normals, and fill them in.
	*/
	Glyph(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[2])
	{
	
		vertecies[0].setColor(color[0]);
		vertecies[1].setColor(color[0]);
		vertecies[2].setColor(color[0]);
		vertecies[3].setColor(color[0]);
		vertecies[4].setColor(color[1]);
		vertecies[5].setColor(color[1]);
		vertecies[6].setColor(color[1]);
		vertecies[7].setColor(color[1]);


		vertecies[0].setPosition(glm::vec3(position.x, position.y, position.z));
		vertecies[1].setPosition(glm::vec3(position.x + scale.x, position.y, position.z));
		vertecies[2].setPosition(glm::vec3(position.x, position.y + scale.y, position.z));
		vertecies[3].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z));
		vertecies[4].setPosition(glm::vec3(position.x, position.y, position.z + scale.z));
		vertecies[5].setPosition(glm::vec3(position.x + scale.x, position.y, position.z + scale.z));
		vertecies[6].setPosition(glm::vec3(position.x, position.y + scale.y, position.z + scale.z));
		vertecies[7].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z + scale.z));
		// calculate the vertexes normal
		glm::vec3 normalVecs[NUMBER_OF_NORMALS_IN_A_CUBE];
		normalVecs[0] = glm::normalize(glm::cross(vertecies[1].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[1] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[1].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[2] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[3] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[1].positionToGlm(), vertecies[5].positionToGlm() - vertecies[1].positionToGlm()));
		normalVecs[4] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[2].positionToGlm(), vertecies[6].positionToGlm() - vertecies[2].positionToGlm()));
		normalVecs[5] = glm::normalize(glm::cross(vertecies[5].positionToGlm() - vertecies[4].positionToGlm(), vertecies[6].positionToGlm() - vertecies[4].positionToGlm()));

		vertecies[0].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[2]);
		vertecies[1].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[3]);
		vertecies[2].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[4]);
		vertecies[3].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[3]);
		vertecies[4].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[5]);
		vertecies[5].setNormal(normalVecs[0] + normalVecs[3] + normalVecs[5]);
		vertecies[6].setNormal(normalVecs[2] + normalVecs[4] + normalVecs[5]);
		vertecies[7].setNormal(normalVecs[3] + normalVecs[4] + normalVecs[5]);


	};
	/*
	Constructor.
	Input:
	-const glm::vec3 &position - the position of the cube in world coordinates (we *currently* do not use a translation matrix).
	-const glm::vec3 &scale - the scale of the cube, in x, y, and z coordiantions.
	-Color8 color[NUMBER_OF_VERTS_IN_GLYPH] - the color of each of the vertecies in the cube, in this order color[0] to vert[0], color[1] to vert[1] and so on.
	Output:
	-Glyph - a glyph object set-up and ready to go.
	Note: the constructor will also calculate the vertecies normals, and fill them in.
	*/
/*	Glyph(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[NUMBER_OF_VERTS_IN_GLYPH])
	{
		for (int i = 0; i < NUMBER_OF_VERTS_IN_GLYPH; i++)
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
		// calculate the vertexes normal
		glm::vec3 normalVecs[NUMBER_OF_NORMALS_IN_A_CUBE];
		normalVecs[0] = glm::normalize(glm::cross(vertecies[1].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[1] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[1].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[2] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[3] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[1].positionToGlm(), vertecies[5].positionToGlm() - vertecies[1].positionToGlm()));
		normalVecs[4] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[2].positionToGlm(), vertecies[6].positionToGlm() - vertecies[2].positionToGlm()));
		normalVecs[5] = glm::normalize(glm::cross(vertecies[5].positionToGlm() - vertecies[4].positionToGlm(), vertecies[6].positionToGlm() - vertecies[4].positionToGlm()));

		vertecies[0].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[2]);
		vertecies[1].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[3]);
		vertecies[2].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[4]);
		vertecies[3].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[3]);
		vertecies[4].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[5]);
		vertecies[5].setNormal(normalVecs[0] + normalVecs[3] + normalVecs[5]);
		vertecies[6].setNormal(normalVecs[2] + normalVecs[4] + normalVecs[5]);
		vertecies[7].setNormal(normalVecs[3] + normalVecs[4] + normalVecs[5]);


	};*/
	/*
	Constructor.
	Input:
	-const glm::vec3 &position - the position of the cube in world coordinates (we *currently* do not use a translation matrix).
	-const glm::vec3 &scale - the scale of the cube, in x, y, and z coordiantions.
	-Color8 color - the color of all of the vertecies in the cube (a cube with 1 color).
	Output:
	-Glyph - a glyph object set-up and ready to go.
	Note: the constructor will also calculate the vertecies normals, and fill them in.
	*/
	Glyph(const glm::vec3 &position, const glm::vec3 &scale, Color8 color)
	{
		for (int i = 0; i < NUMBER_OF_VERTS_IN_GLYPH; i++)
		{
			vertecies[i].color = color;
		}
		vertecies[0].setPosition(glm::vec3(position.x, position.y, position.z));
		vertecies[1].setPosition(glm::vec3(position.x + scale.x, position.y, position.z));
		vertecies[2].setPosition(glm::vec3(position.x, position.y + scale.y, position.z));
		vertecies[3].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z));
		vertecies[4].setPosition(glm::vec3(position.x, position.y, position.z + scale.z));
		vertecies[5].setPosition(glm::vec3(position.x + scale.x, position.y, position.z + scale.z));
		vertecies[6].setPosition(glm::vec3(position.x, position.y + scale.y, position.z + scale.z));
		vertecies[7].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z + scale.z));

		glm::vec3 normalVecs[NUMBER_OF_NORMALS_IN_A_CUBE];
		normalVecs[0] = glm::normalize(glm::cross(vertecies[1].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[1] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[1].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[2] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[3] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[1].positionToGlm(), vertecies[5].positionToGlm() - vertecies[1].positionToGlm()));
		normalVecs[4] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[2].positionToGlm(), vertecies[6].positionToGlm() - vertecies[2].positionToGlm()));
		normalVecs[5] = glm::normalize(glm::cross(vertecies[5].positionToGlm() - vertecies[4].positionToGlm(), vertecies[6].positionToGlm() - vertecies[4].positionToGlm()));

		vertecies[0].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[2]);
		vertecies[1].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[3]);
		vertecies[2].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[4]);
		vertecies[3].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[3]);
		vertecies[4].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[5]);
		vertecies[5].setNormal(normalVecs[0] + normalVecs[3] + normalVecs[5]);
		vertecies[6].setNormal(normalVecs[2] + normalVecs[4] + normalVecs[5]);
		vertecies[7].setNormal(normalVecs[3] + normalVecs[4] + normalVecs[5]);


	};
	/*
	The glyph's vertecies array.
	*/
	Vertex vertecies[NUMBER_OF_VERTS_IN_GLYPH];
private:
	/*
	none as of now.
	*/
};
/*
 The RenderBatch class.
 contains information that helps render things that have different textures.
*/
class RenderBatch
{
public:
	/*
	Constructor.
	Input: 
		-GLuint Offset - the offset in number of indecies from the last RenderBatch. should be 0 for the first RenderBatch.
		-GLuint Numvertecies - the number of vertecies the RenderBatch will draw. (TODO: Change to NumIndecies, not vertecies).
	Output:
		-RenderBatch - a RenderBatch object with information for the draw phase.
	*/
	RenderBatch(GLuint Offset, GLuint Numvertecies) : offset(Offset), numVertecies(Numvertecies)
	{
		//Empty
	}
	GLuint offset;
	GLuint numVertecies;
	
};
/*
The DrawBatch class.
contains all the information that is needed for drawing, and interacts with opengl.
*/
class DrawBatch
{
public:
	/*
	Create a DrawBatch object.
	Empty.
	*/
	DrawBatch();
	/*
	Destroy a DrawBatch object.
	Empty.
	*/
	~DrawBatch();
	/*
	Initialize the DrawBatch object.
	Input: 
		-Camera3D* camera - a pointer to the main camera being used in the game. for frustum calculations.
	*/
	void init(Camera3D *camera);
	/*
	Start the Rendering sequence.
	will clear Vectors and cacluate frustum.
	Should be called before the draw calls.
	*/
	void start();
	/*
	Ends the Rendering sequence.
	Will call createRenderBatches().
	Should be called after all the draw calls, and before renderBatch().
	*/
	void end();
	/*
	Draw a cube.
	Input:
		-const glm::vec3 &position - the position of the cube in world coordinates (we *currently* do not use a translation matrix).
		-const glm::vec3 &scale - the scale of the cube, in x, y, and z coordiantions.
		-Color8 color[NUMBER_OF_VERTS_IN_GLYPH] - the color of each of the vertecies in the cube, in this order color[0] to vert[0], color[1] to vert[1] and so on.
		-bool overrideFrustum = false - should the cube override the frustum culling? true for yes, false for no. default parameter is false.
	Should be called before end() and after start().
	*/
	void draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[NUMBER_OF_VERTS_IN_GLYPH], bool overrideFrustum = false);
	/*
	Draw a cube.
	Input:
		-const glm::vec3 &position - the position of the cube in world coordinates (we *currently* do not use a translation matrix).
		-const glm::vec3 &scale - the scale of the cube, in x, y, and z coordiantions.
		-Color8 color - the color of all of the vertecies in the cube (a cube with 1 color).
		-bool overrideFrustum = false - should the cube override the frustum culling? true for yes, false for no. default parameter is false.
	Should be called before end() and after start().
	*/
	void draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 &color, bool overrideFrustum = false);
	/*
	Render the batches.
	will render all the previous draw calls.
	Should be called after end()
	*/
	void renderBatch();
	/*
	Dispose the buffers anmd deletes them.
	Should be called after the end of the game-loop.
	*/
	void dispose();

private:
	/*
	Create the render batches.
	Fills a vector of vertecies with the vertex data, and uploads it to a buffer.
	Fills a vector of indecies with the indecies data, and uploads it to a buffer.
	*/
	void createRenderBatches(); 
	/*
	Create the buffers and vertex array object, and make them bound to the vertex array object.
	*/
	void createVertexArray();

	bool lastBatchChecked;
	bool lastBatchInFrustum;

	Camera3D *m_camera;
	GLuint m_vbo, m_vao, m_ibo; // vertex buffer object, vertex array object, indecies buffer object

	std::vector<Glyph> m_glyphs;
	std::vector<RenderBatch> m_renderBatches; 
	std::vector<GLuint> m_indecies;

	GLuint m_numElements;

};
																							
