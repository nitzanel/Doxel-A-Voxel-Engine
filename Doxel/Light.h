#pragma once
#include <glm\glm.hpp>
#include "Vertex.h"
#include "GLProgram.h"

struct Color3f
{

	/*
	Color constructor of white color.
	*/
	Color3f() : r(1.0), g(1.0), b(1.0) {};
	/*
	Color contructor of a specific color.
	*/
	Color3f(float R, float G, float B) : r(R), g(G), b(B) {};

	float r, g, b;
};

struct Color3
{	
	/*
	Color constructor of white color.
	*/
	Color3() :r(255), b(255), g(255){};
	/*
	Color contructor of a specific color.
	*/
	Color3(byte R, byte G, byte B) : r(R), g(G), b(B) {};

	byte r, g, b;
};

class Light
{
public:
	Light() {/*EMPTY*/};
	~Light(){/*EMPTY*/ };
	/*
	initialize the light.
	*/
	void init(const glm::vec3 &position, Color3f color, float intesnsity, GLProgram *program)
	{
		if (intesnsity >= 0.0f && intesnsity <= 1.0f)
		{
			m_intensity = intesnsity;
		}
		else
		{
			Debug_Log("bad light intensity input! the value should be between 0 and 1");
			m_intensity = 1.0f;
		}
		m_position = position;
		m_color = color;
		shouldUpdate = true;
		m_program = program;
	}
	/*
	upadtes the light data in the shader.
	*/
	void update()
	{
		if (shouldUpdate)
		{
			m_program->uploadUniformFloat("lightIntensity", 1, m_intensity);
			m_program->uploadUniformVector3("lightPosition_worldSpace", 1, m_position);
			m_program->uploadUniformVector4("lightColor", 1, glm::vec4(m_color.r,m_color.g,m_color.b, 1.0));
		}
		else
		{
			return;
		}
	}

	/*
	getters
	*/
	/*
	returns the light position.
	*/
	glm::vec3 getPosition() { return m_position; }
	/*
	returns the light color.
	*/
	Color3f getColor() { return m_color; }
	/*
	returns the light intensity.
	*/
	float getLightIntesity() { return m_intensity; }
	/*
	setters.
	*/
	/*
	set the light position.
	*/
	void setPosition(glm::vec3 pos) { m_position = pos; shouldUpdate = true; }
	/*
	set the light intensity.
	*/
	void setLightIntensity(float intensity) { m_intensity = intensity;  shouldUpdate = true; }
	/*
	set the light color.
	*/
	void setColor(Color3f color) { m_color = color; shouldUpdate = true; }

private:
	glm::vec3 m_position; // maybe a 2 shorts position with z that stays the same (or xz that chagnes)
	float m_intensity;
	Color3f m_color;
	GLProgram *m_program;
	bool shouldUpdate = false;

};

