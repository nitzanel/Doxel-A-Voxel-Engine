#pragma once
#include <glm\glm.hpp>
#include "DrawBatch.h"
#include <random>
#include "Vertex.h"

#define CHUNK_SIZE  8
#define NUM_CHUNKS 10
#define BLOCK_WIDTH 1
#define EPSILON 0.001
#define RENDER_DISTANCE 200.0f



enum GEN_METHOD
{
	RANDOM, SPHERE, ALL
};


struct Row
{
	Row()
	{};
	Row(byte Start, byte End,bool Grass,bool shouldDraw)
	{
		shouldbeDrawn = shouldDraw;
		grass = Grass;
		start = Start;
		end = End;
		length = end - start + 1;
	}
	void Update()
	{
		length = end - start + 1;
	}
	byte start;
	byte end;
	byte length;
	bool grass;
	bool shouldbeDrawn;
	
};
/*
BlockClicked struct.
*/
struct BlockClicked
{
	/*
	set the chunk of the block clicked
	*/
	void setChunk(unsigned int x, unsigned int z)
	{
		chunkX = x;
		chunkZ = z;
	}
	/*
	set the block of the block clicked.
	*/
	void setBlock(unsigned int x, unsigned int y, unsigned int z)
	{
		blockX = x;
		blockY = y;
		blockZ = z;
	}

	unsigned int chunkX, chunkZ, blockX, blockY, blockZ;
	float distance;
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
///< Chunk class needs to be rewritten in more organaized way, there are too many public veriables
class Chunk
{
public:
	/*
	Create a chunk object.
	An empty constructor.
	*/
	Chunk();
	/*
	Destroy a chunk object, and delete the blocks data.
	*/
	~Chunk();

	bool isActive = false;
	bool shouldUpdate = true;
	bool isInit = false;
	/*
	Set the chunk generation method
	Input:
		- GEN_METHOD method-	*ALL for all cubes to be renderd.
								*RANDOM for some of the cubes to be renderd.
								*SOHERE for a sphere like figure of the chunk to be renderd.
	
	*/
	void setGenMethod(GEN_METHOD method) 
	{		
			m_genMethod = method;
			shouldUpdate = true;		
	}
	/*
	Returns true if a block is active, false if not.
	*/
	bool getActiveBlock(unsigned int x, unsigned int y, unsigned int z)
	{
		if (isInit)
		{
			if (m_blocks[x][y][z].getActive())
			{
				return true;
			}
		}
			return false;
		
	}

	/*
	Init the chunk.
	TODO: after chunks get disposed for being out of render range, make sure to redraw them when they are back again in the render range.
	*/
	void init();
	/*
	Dipose the chunk.
	TODO: after chunks get disposed for being out of render range, make sure to redraw them when they are back again in the render range.(mostly work in Chunk::init())
	*/
	void dispose();
	/*
	Draw the chunk.
	Input:
		-DrawBatch* drawBatch - a pointer to the DrawBatch object being used to draw the scene.
		- glm::vec2 &ChunkPos- a reference to a glm::vec2 that contains the position of the chunk on the 2D grid of the chunks.
	*/
	void draw(DrawBatch* drawBatch, glm::vec2 &ChunkPos);
	/*
	Update the chunks.
	Will set only happen if shouldUpdate = true.
	will generate the blocks according to the m_genMethod.
	*/
	void update(); 
	/*
	Sets the chunk's state.
	Input:
		-bool state - true for active, false for not active.
	*/
	void setActive(bool state);
	/*
	Sets the chunk's color.
	Input:	
		-Color8 color - the color you want the chunk to have.
	*/
	void setColor(Color8 color) { m_color = color; }
	/*
	Generate the chunk randomly.
	Input: 
		-int numBlocks - the number of active blocks the chunk will have.
	*/
	void genRand(int numBlocks);
	/*
	Generate the chunk in a sphere-like figure.
	*/
	void genSphere();
	/*
	Generate all the blocks in the chunk.
	*/
	void genAll();
	/*
	Activate or deactivate a block
	*/
	void setBlock(unsigned int x, unsigned int y, unsigned int z,bool state)
	{
		m_blocks[x][y][z].setActive(state);
	}
	
private:
	Block*** m_blocks;
	Color8 m_color;
	GEN_METHOD m_genMethod = GEN_METHOD::ALL;
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
	/*
	Activate or deactivate a specific block in a specific chunk.
	Input:
	-BlockClicked blockClicked - a BlockClicked struct with all the information needed.
	-bool state- the new state of the block.
	*/
	void setBlock(BlockClicked blockClicked,bool state)
	{
		setBlock(blockClicked.chunkX, blockClicked.chunkZ, blockClicked.blockX, blockClicked.blockY, blockClicked.blockZ, state);
	}
	
	/*
	Activate or deactivate a specific block in a specific chunk.
	*/
	void setBlock(unsigned chunkX, unsigned chunkZ, unsigned int blockX, unsigned int blockY, unsigned int blockZ, bool state)
	{
		m_chunks[chunkX][chunkZ].setBlock(blockX, blockY, blockZ, state);
	}
	/*
	returns if a block is active, takes a BlockClicked struct.
	*/
	bool getActiveBlock(BlockClicked blockClicked)
	{
		getActiveBlock(blockClicked.chunkX, blockClicked.chunkZ, blockClicked.blockX, blockClicked.blockY, blockClicked.blockZ);
	}
	/*
	returns if a block is active
	*/
	bool getActiveBlock(unsigned chunkX, unsigned chunkZ, unsigned int blockX, unsigned int blockY, unsigned int blockZ)
	{
		return m_chunks[chunkX][chunkZ].getActiveBlock(blockX, blockY, blockZ);
	}
	/*
	returns if a chunk is active
	*/
	bool getActiveChunk(unsigned chunkX, unsigned chunkZ)
	{
		return m_chunks[chunkX][chunkZ].isActive;
	}
private:
	glm::vec3 lastCameraPos;
	Chunk** m_chunks;
	int m_chunksDraw = 0;
};

