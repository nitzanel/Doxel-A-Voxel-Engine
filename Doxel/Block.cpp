#include "Block.h"
#include "EasyErrors.h"
#include <ctime>

std::mt19937 randEngine(time(NULL));
std::uniform_int_distribution<int> distribution(0, 255);
std::uniform_int_distribution<int> roll(0, CHUNK_SIZE - 1);
std::uniform_int_distribution<int> randBand(0, CHUNK_SIZE *CHUNK_SIZE*CHUNK_SIZE);
std::uniform_int_distribution<int> randBool(0, 1);


Block::Block()
{
}


Block::~Block()
{
}


Chunk::Chunk()
{
	

}

Chunk::~Chunk()
{
	if (!isInit)
	{
		return;
	}
	// Delete the blocks
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			
			delete[] m_blocks[i][j];
		}

		delete[] m_blocks[i];
	}
	delete[] m_blocks;

}



void Chunk::init()
{


	if (!isInit)
	{
		// Create the blocks
		m_blocks = new Block**[CHUNK_SIZE];
	
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			m_blocks[i] = new Block*[CHUNK_SIZE];

			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				m_blocks[i][j] = new Block[CHUNK_SIZE];
			}
		}
		if (!wasInit){
			int R = distribution(randEngine);
			int G = distribution(randEngine);
			int B = distribution(randEngine);
			m_color = Color8(R, G, B, 255);
			wasInit = true;
		}
		isInit = true;
	}
}
void Chunk::dispose()
{
	if (!isInit)
	{
		return;
	}
	// Delete the blocks
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{

			delete[] m_blocks[i][j];
		}

		delete[] m_blocks[i];
	}
	delete[] m_blocks;
	isInit = false;
}
void Chunk::update()
{
	if (shouldUpdate)
	{
		switch (m_genMethod)
		{
		case RANDOM:
			genRand(randBand(randEngine));
			break;
		case SPHERE:
			genSphere();
			break;
		case ALL:
			genAll();
			break;
		default:
			Debug_Log(" ERROR? : genMethod = NONE");
			break;
		}
	}
	shouldUpdate = false;
}

void Chunk::setActive(bool state)
{
	 isActive = state;
}

void Chunk::draw(DrawBatch* drawBatch, glm::vec2 &ChunkPos)
{
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				if (m_blocks[i][j][k].getActive())
				{
					glm::vec3 bPos(ChunkPos.x +i ,ChunkPos.y + j,k);
					drawBatch->draw(bPos, glm::vec3(1.0), m_color);
					
				}
			}
		}
	}
}
void Chunk::genRand(int numBlocks)
{
	int numActive = 0;

	if (numBlocks > (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE))
	{
		Debug_Log("Bad input for randActive");
	}
	else
	{

		for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
		{
			int x, y, z;
			x = roll(randEngine);
			y = roll(randEngine);
			z = roll(randEngine);

			if (randBool(randEngine))
			{

				if (!m_blocks[x][y][z].getActive())
				{
					m_blocks[x][y][z].setActive(true);
				}
				numActive++;
				if (numActive >= numBlocks / 3)
				{
					return;
				}
			}
			else
			{
				m_blocks[x][y][z].setActive(false);
			}
		}
	}
}


void Chunk::genSphere()
{
	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				if (sqrt((float)(x - CHUNK_SIZE / 2)*(x - CHUNK_SIZE / 2) + (y - CHUNK_SIZE / 2)*(y - CHUNK_SIZE / 2) + (z - CHUNK_SIZE / 2)*(z - CHUNK_SIZE / 2)) < CHUNK_SIZE / 2)
				{
					m_blocks[x][y][z].setActive(true);
				}
				else
				{
					m_blocks[x][y][z].setActive(false);
				}
			}
		}
	}
}
void Chunk::genAll()
{
	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				m_blocks[x][y][z].setActive(true);
			}

		}
	}
}

ChunkManager::ChunkManager()
{

}
void ChunkManager::init()
{
	m_chunks = new Chunk*[NUM_CHUNKS];
	for (int i = 0; i < NUM_CHUNKS; i++)
	{
		m_chunks[i] = new Chunk[NUM_CHUNKS];
	/*	for (int j = 0; j < NUM_CHUNKS; j++)
		{
		//	m_chunks[i][j].init();
		}*/
	}
}

ChunkManager::~ChunkManager()
{
	delete[] m_chunks;
	m_chunks = nullptr;
}

void ChunkManager::update(const glm::vec3 &cameraPos)
{
	glm::vec2 cameraPosXY(cameraPos.x, cameraPos.y);

	Debug_Log(m_chunksDraw);
	m_chunksDraw = 0;
	
	for (int i = 0; i < NUM_CHUNKS; i++)
		{
			for (int j = 0; j < NUM_CHUNKS; j++)
			{
				glm::vec2 chunkPos(i * CHUNK_SIZE * BLOCK_WIDTH, j * CHUNK_SIZE * BLOCK_WIDTH);
				glm::vec2 dist = cameraPosXY - chunkPos;
				

				//if (glm::abs(glm::distance(cameraPosXY, chunkPos)) < RENDER_DISTANCE)
				if (glm::abs(glm::length(dist)) < RENDER_DISTANCE)
				{	
					//Debug_Log(glm::distance(cameraPosXY, chunkPos));
					m_chunks[i][j].init();
					m_chunks[i][j].setActive(true);
					m_chunks[i][j].update();
				}
				else
				{
					m_chunks[i][j].dispose();
				}
			}			
		}



	//	lastCameraPos = cameraPos;
	//}
}
void ChunkManager::setGenMethod(GEN_METHOD method)
{
	for (int i = 0; i < NUM_CHUNKS; i++)
	{
		for (int j = 0; j < NUM_CHUNKS; j++)
		{
			m_chunks[i][j].setGenMethod(method);
		}
	}
}

void ChunkManager::draw(DrawBatch* drawBatch)
{
	for (int i = 0; i < NUM_CHUNKS; i++)
	{
		for (int j = 0; j < NUM_CHUNKS; j++)
		{
			if (m_chunks[i][j].isActive)
			{
				if (m_chunks[i][j].isInit)
				{
					m_chunks[i][j].draw(drawBatch, glm::vec2(i * CHUNK_SIZE + i, j * CHUNK_SIZE + j));
					m_chunksDraw++;
				}
			}
		}
	}
}
