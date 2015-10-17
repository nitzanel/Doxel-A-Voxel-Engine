/*
FILE DESCRIPTION

This file contains:
The enum DRAW_TYPE, which is used in the Renderer class.
The Polygon class.
The abstract Renderer class.
*/
#pragma once
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Doxel.h"
#include "Vertex.h"
#include "Camera3D.h"

enum DRAW_TYPE
{
	LINES,TRIANGLES,QUADS 
};

class Polygon
{
	/*
	The default empty costructor.
	*/
	Polygon(){/*Empty*/};
	/*
	**** Arc-like polygons ****
	*/
	
	/*
	Constructor.
	Input:
	-const glm::vec3 &position - the position of the arc in world coordinates (we *currently* do not use a translation matrix).
	-const glm::vec3 &scale - the scale of the arc, in x, y, and z coordiantions.
	-Color8 color - the color of the arc.
	Output:
	-Polygon - a Polygon object set-up and ready to go.
	Note: the constructor will also calculate the vertecies normals, and fill them in.
	*/	
	Polygon(const glm::vec3 &position, const glm::vec3 &scale, Color8 color)
	{
		// cretae 8 vertecies for the polygon(arc-like)
		vertecies.reserve(NUM_OF_VERTECIES_IN_AN_ARC);
		// set the vertecies color.
		for (int i = 0; i < NUM_OF_VERTECIES_IN_AN_ARC; i++)
		{
			vertecies[i].setColor(color);
		}
		// set the vetecies position
		vertecies[0].setPosition(glm::vec3(position.x, position.y, position.z));
		vertecies[1].setPosition(glm::vec3(position.x + scale.x, position.y, position.z));
		vertecies[2].setPosition(glm::vec3(position.x, position.y, position.z + scale.z));
		vertecies[3].setPosition(glm::vec3(position.x + scale.x, position.y, position.z + scale.z));
		vertecies[4].setPosition(glm::vec3(position.x, position.y + scale.y, position.z));
		vertecies[5].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z));
		vertecies[6].setPosition(glm::vec3(position.x, position.y + scale.y, position.z + scale.z));
		vertecies[7].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z + scale.z));

		glm::vec3 normalVecs[NUM_OF_NORMALS_IN_AN_ARC];
		// Calculate the arc normals.
		normalVecs[0] = glm::normalize(glm::cross(vertecies[1].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[1] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[1].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[2] = glm::normalize(glm::cross(vertecies[4].positionToGlm() - vertecies[0].positionToGlm(), vertecies[2].positionToGlm() - vertecies[0].positionToGlm()));
		normalVecs[3] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[1].positionToGlm(), vertecies[5].positionToGlm() - vertecies[1].positionToGlm()));
		normalVecs[4] = glm::normalize(glm::cross(vertecies[3].positionToGlm() - vertecies[2].positionToGlm(), vertecies[6].positionToGlm() - vertecies[2].positionToGlm()));
		normalVecs[5] = glm::normalize(glm::cross(vertecies[5].positionToGlm() - vertecies[4].positionToGlm(), vertecies[6].positionToGlm() - vertecies[4].positionToGlm()));
		// Calculate the vertecies normals.
		vertecies[0].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[2]);
		vertecies[1].setNormal(normalVecs[0] + normalVecs[1] + normalVecs[3]);
		vertecies[2].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[4]);
		vertecies[3].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[3]);
		vertecies[4].setNormal(normalVecs[0] + normalVecs[2] + normalVecs[5]);
		vertecies[5].setNormal(normalVecs[0] + normalVecs[3] + normalVecs[5]);
		vertecies[6].setNormal(normalVecs[2] + normalVecs[4] + normalVecs[5]);
		vertecies[7].setNormal(normalVecs[3] + normalVecs[4] + normalVecs[5]);


	}
	/*
	 Constructor.
	 Input:
	 -const glm::vec3 &position - the position of the arc in world coordinates (we *currently* do not use a translation matrix).
	 -const glm::vec3 &scale - the scale of the arc, in x, y, and z coordiantions.
	 -Color8 color[2] - color[0] of the top face of the arc.
						color[1] the color of the rest of the faces.
	 Output:
	 -Polygon - a Polygon object set-up and ready to go.
	 Note: the constructor will also calculate the vertecies normals, and fill them in.
	 */		
	Polygon(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[2])
	{
		vertecies.reserve(NUM_OF_VERTECIES_IN_A_DOUBLE_COLOR_ARC);
		for (int i = 0; i < NUM_OF_VERTECIES_IN_A_DOUBLE_COLOR_ARC; i++)
		{
			if (i < NUM_OF_VERTECIES_IN_AN_ARC)
			{
				vertecies[i].setColor(color[1]);
			}
			else
			{
				vertecies[i].setColor(color[0]);
			}
		}
		vertecies[0].setPosition(glm::vec3(position.x, position.y, position.z));
		vertecies[1].setPosition(glm::vec3(position.x + scale.x, position.y, position.z));
		vertecies[2].setPosition(glm::vec3(position.x, position.y, position.z + scale.z));
		vertecies[3].setPosition(glm::vec3(position.x + scale.x, position.y, position.z + scale.z));
		vertecies[4].setPosition(glm::vec3(position.x, position.y + scale.y, position.z));
		vertecies[5].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z));
		vertecies[6].setPosition(glm::vec3(position.x, position.y + scale.y, position.z + scale.z));
		vertecies[7].setPosition(glm::vec3(position.x + scale.x, position.y + scale.y, position.z + scale.z));

	}
	/*
	**** More compicated polygon constructors ****
	this is a Voxel Engine. so no need for such things.
	*/

	std::vector<Vertex> vertecies;
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	/*
	Initialize the Renderer.
	Input: 
		-Camera3D* camera - a pointer to the main camera being used in the game. for frustum culling.
	*/
	void init(Camera3D *camera);
	
	/*
	Dispose the Renderer.
	*/
	void dispose();
	
	/*
	Start the rendering sequence.
	*/
	void start();
	
	/*
	Ends the Rendering sequence.
	*/
	void end();
	
	/*
	Render the batch.
	*/
	void renderBatch();

	/*
	**** Draw calls to match Polygon class ****
	*/
	void draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 color);
	void draw(const glm::vec3 &position, const glm::vec3 &scale, Color8 color[2]);

protected:
	/*
	Create the render batches.
	Fills a vector of vertecies with the vertex data, and uploads it to a buffer.
	Fills a vector of indecies with the indecies data, and uploads it to a buffer.
	is a pure virtual function.
	*/
	virtual void createRenderBatches() = 0;
	/*
	Create the buffers and vertex array object, and make them bound to the vertex array object.
	can be overrided
	*/
	virtual void createVertexArray();

	bool lastBatchChecked;
	bool lastBatchInFrustum;

	Camera3D *m_camera;
	GLuint m_vbo, m_vao, m_ibo; // vertex buffer object, vertex array object, indecies buffer object

	std::vector<Polygon> m_polygons;
//	std::vector<RenderBatch> m_renderBatches; turned off until actual implentaion
	std::vector<GLuint> m_indecies;

	GLuint m_numElements;
	DRAW_TYPE m_drawType;
};


