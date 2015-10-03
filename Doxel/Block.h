#pragma once
#include <glm\glm.hpp>
#include "DrawBatch.h"
#include <random>
#include "Vertex.h"

#define CHUNK_SIZE  8
#define NUM_CHUNKS 10
#define BLOCK_WIDTH 1
#define EPSILON 0.001

enum GEN_METHOD
{
	RANDOM, SPHERE, ALL
};

class Block
{
public:
	Block();
	~Block();
	/*
	This function will active or deactive the block.
	Input:
		- bool state - the wanted state of the block, true for active, false for deactive.
	*/
	void setActive(bool state) { isActive = state; }
	/*
	This function will return the state of the block.
	*/
	bool getActive() { return isActive; }

private:
	bool isActive = false;

	
};
///< Chunk class needs to be rewritten in more organaized way.
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
	void genAll();
	
private:
	Block*** m_blocks;
	Color8 m_color;
	GEN_METHOD m_genMethod = GEN_METHOD::RANDOM;
	bool wasInit = false;
};

class ChunkManager
{
public:
	/*
	Create a ChunkManager.
	*/
	ChunkManager();
	/*
	Destroy a Chunkmanager.
	*/
	~ChunkManager();
	/*
	Initialize the ChunkManager.
	*/
	void init();
	/*
	Dispose the ChunkManager. /// make program crush, check destructor.
	*/
	void dispose() { this->~ChunkManager();	}
	/*
	This function updates the ChunkManager.
	Input:
		- const glm::vec3 &cameraPos - the camera position.
	*/
	void update(const glm::vec3 &cameraPos);
	/*
	This function sets the chunks generation method.
	Input:
		- GEN_METHOD method -	* RANDOM for randomized generation.
								* SPHERE for sphere like generation.
								* ALL for all blocks to be generated.
	*/
	void setGenMethod(GEN_METHOD method);
	/*
	This function will call the draw function in the needed chunks.
	Input:
		- DrawBatch* drawBatch - a pointer to the DrawBatch object that will draw the chunks. 
	*/
	void draw(DrawBatch* drawBatch);


	glm::vec3 lastCameraPos;
private:
	Chunk** m_chunks;
	int m_chunksDraw = 0;
};
