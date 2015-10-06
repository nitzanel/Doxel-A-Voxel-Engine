#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

typedef unsigned char byte;

/*
The Position struct.
*/
struct Position 
{
	float x, y, z;
};
struct PositionByte 
{
	byte x, y, z,w;
};
/*
Normal in bytes.
Note : only works with non-rotated cubes.
additional note, byte w can be used for what-ever.
*/
struct NormalByte
{
	byte x, y, z, w;
};


/*
The Normal struct.
*/
struct Normal
{
	float x, y, z;
};



/*
The Color8 struct.
*/
struct Color8 
{
	/*
	The default constructor that sets the color to black with alpha = 0.
	*/
	Color8() : r(0), g(0), b(0), a(0) { /*EMPTY*/ }
	/*
	Constructor that sets the color according to the input.
	*/
	Color8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) { }
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};
/*
The Vertex struct.
A struct that contains other struct.
Also known as composition struct.
*/
struct Vertex
{
	/*
	position object.
	*/
	Position position;
	/*
	color object.
	*/
	Color8 color;
	/*
	normal object.
	*/
	NormalByte normal;
	/*
	Set the position of the vertex.
	Input:
 		-glm::vec3 pos - the position to set to.
	*/
	void setPosition(glm::vec3 pos)
	{
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
	}
	/*
	Set the position of the vertex.
	Input:
		-float x - the x value.
		-float y - the y value.
		-float z - the z value.	
	*/
	void setPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
	/*
	Set the vertex color.
	Input:
		-Color8 col - a color object that will be the new color of the vertex.
	*/
	void setColor(Color8 col)
	{
		color = col;
	}
	/*
	Set the vertex color.
	Input:
		-GLubyte r - the red value of the color.
		-GLubyte g - the green value of the color.
		-GLubyte b - the blue value of the color.
		-GLubyte a - the alpha value of the color.
	*/
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	/*
	Set the vertex normal.
	Input:
		-glm::vec3 normalVec - the normal vector.
	*/
	void setNormal(glm::vec3 normalVec)
	{
		normal.x = normalVec.x;
		normal.y = normalVec.y;
		normal.z = normalVec.z;
	}
	/*
	Set the vertex normal.
	Input:
	-float x - the x value.
	-float y - the y value.
	-float z - the z value.
	*/
	void setNormal(float x, float y, float z)
	{
		normal.x = x;
		normal.y = y;
		normal.z = z;
	}
	/*
	returns the position value as a glm::vec3.
	*/
	glm::vec3 positionToGlm()
	{
		return glm::vec3(position.x, position.y, position.z);
	}
};

// TODO - Change shaders to match new vertex data
// DONE.