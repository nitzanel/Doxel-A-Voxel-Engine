#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

struct Position {

	float x, y, z;
};

struct Normal
{
	float x, y, z;
};

struct Color8 {
	Color8() : r(0), g(0), b(0), a(0) { }
	Color8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) { }
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex{

	Position position;

	Color8 color;

	Normal normal;

	void setPosition(glm::vec3 pos)
	{
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
	}
	void setPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void setColor(Color8 col)
	{
		color = col;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	void setNormal(glm::vec3 normalVec)
	{
		normal.x = normalVec.x;
		normal.y = normalVec.y;
		normal.z = normalVec.z;
	}
	void setNormal(float x, float y, float z)
	{
		normal.x = x;
		normal.y = y;
		normal.z = z;
	}
	glm::vec3 positionToGlm()
	{
		return glm::vec3(position.x, position.y, position.z);
	}
};

// TODO - Change shaders to match new vertex data