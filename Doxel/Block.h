#pragma once
#include <glm\glm.hpp>
#include "DrawBatch.h"
#include <random>
#include "Vertex.h"
const int CHUNKSIZE = 8;
const int NUM_CHUNKS = 100;



enum GEN_METHOD
{
	RANDOM, SPHERE
};

class Block
{
public:
	Block();
	~Block();

	void setActive(bool state) { isActive = state; }
	bool getActive() { return isActive; }

private:
	bool isActive = false;

	
};

class Chunk
{
public:
	Chunk();
	~Chunk();


	bool isActive = false;
	bool shouldUpdate = true;
	bool isInit = false;
	void setGenMethod(GEN_METHOD method) 
	{		
			m_genMethod = method;
			shouldUpdate = true;
		
	}


	void init();
	void dispose();
	void draw(DrawBatch* drawBatch, glm::vec2 &ChunkPos);

	void update(); 
	void setActive(bool state);
	void setColor(Color8 color) { m_color = color; }

	void genRand(int numBlocks);
	void genSphere();
	
private:
	Block*** m_blocks;
	Color8 m_color;
	GEN_METHOD m_genMethod = GEN_METHOD::RANDOM;
	bool wasInit = false;
};

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void init();
	void dispose() { this->~ChunkManager();	}

	void update(const glm::vec3 &cameraPos);
	void setGenMethod(GEN_METHOD method);
	void draw(DrawBatch* drawBatch);


	glm::vec3 lastCameraPos;
private:
	Chunk** m_chunks;
	int m_chunksDraw = 0;
};
