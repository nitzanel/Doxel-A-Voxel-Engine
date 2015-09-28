#pragma once
#include <glm\glm.hpp>
#include "DrawBatch.h"
#include <random>
#include "Vertex.h"
const int CHUNKSIZE = 8;
const int NUM_CHUNKS = 1000;




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
	bool shouldUpdate = false;
	bool isInit = false;

	void init();
	void dispose();
	void draw(DrawBatch* drawBatch, glm::vec2 &ChunkPos);

	void update(); 
	void setActive(bool state);
	void setColor(Color8 color) { m_color = color; }

	void randActive(int numBlocks);

private:
	Block*** m_blocks;
	Color8 m_color;
};

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void init();
	void dispose() {
		this->~ChunkManager();
	}
	void update(const glm::vec3 &cameraPos);

	void draw(DrawBatch* drawBatch);


	glm::vec3 lastCameraPos;
private:
	Chunk** m_chunks;
	int m_chunksDraw = 0;
};
