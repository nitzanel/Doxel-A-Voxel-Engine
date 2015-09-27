#pragma once
#include <glm\glm.hpp>
#include "DrawBatch.h"
#include <random>
#include "Vertex.h"
const int CHUNKSIZE = 8;
const int NUM_CHUNKS = 1;




class Block
{
public:
	Block();
	~Block();

	void setActive(bool state) { isActive = state; }
	bool getActive() { return isActive; }

private:
	bool isActive;

	
};

class Chunk
{
public:
	Chunk();
	~Chunk();


	bool isActive = false;
	bool shouldUpdate = false;
	Color8 m_color;
	
	void init();

	void draw(DrawBatch* drawBatch, glm::vec2 &ChunkPos);

	void update(); 
	void setActive(bool state);

private:
	Block*** m_blocks;
};

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void init();

	void update(const glm::vec3 &cameraPos);

	void draw(DrawBatch* drawBatch);


	glm::vec3 lastCameraPos;
private:
	Chunk** m_chunks;
	int m_chunksDraw = 0;
};
