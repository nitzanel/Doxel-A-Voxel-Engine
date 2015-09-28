#include "Block.h"
#include "EasyErrors.h"
#include <ctime>
const float RENDER_DISTANCE = 100.0f;

std::mt19937 randEngine(time(NULL));
std::uniform_int_distribution<int> distribution(0, 255);
std::uniform_int_distribution<int> roll(0, CHUNKSIZE - 1);
std::uniform_int_distribution<int> randBand(0, CHUNKSIZE *CHUNKSIZE*CHUNKSIZE);
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
	for (int i = 0; i < CHUNKSIZE; i++)
	{
		for (int j = 0; j < CHUNKSIZE; j++)
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
		m_blocks = new Block**[CHUNKSIZE];
		for (int i = 0; i < CHUNKSIZE; i++)
		{
			m_blocks[i] = new Block*[CHUNKSIZE];

			for (int j = 0; j < CHUNKSIZE; j++)
			{
				m_blocks[i][j] = new Block[CHUNKSIZE];
			}
		}
		int R = distribution(randEngine);
		int G = distribution(randEngine);
		int B = distribution(randEngine);
		m_color = Color8(R, G, B, 255);
		randActive(randBand(randEngine));
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
	for (int i = 0; i < CHUNKSIZE; i++)
	{
		for (int j = 0; j < CHUNKSIZE; j++)
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

/*	if (shouldUpdate)
	{
		for (int i = 0; i < CHUNKSIZE; i++)
		{
			for (int j = 0; j < CHUNKSIZE; j++)
			{
				for (int k = 0; k < CHUNKSIZE; k++)
				{
					if (isActive)
					{
						m_blocks[i][j]->setActive(isActive);
					}
					else
					{
						m_blocks[i][j]->setActive(isActive);
					}
				}

			}
		}
		shouldUpdate = false;
	}*/

}

void Chunk::setActive(bool state)
{
	 isActive = state;
	 shouldUpdate = true; 
}

void Chunk::draw(DrawBatch* drawBatch, glm::vec2 &ChunkPos)
{
	for (int i = 0; i < CHUNKSIZE; i++)
	{
		for (int j = 0; j < CHUNKSIZE; j++)
		{
			for (int k = 0; k < CHUNKSIZE; k++)
			{
				if (m_blocks[i][j][k].getActive())
				{
				//	glm::vec3 bPos(ChunkPos.x +2 * i * sinf(i * k), sinf(i *j) * j + ChunkPos.y, cosf(2 * k) * k * j); ///< can multiply by size of block
	//				glm::vec3 bPos(ChunkPos.x +  sinf(i * j) * i, j * cosf(j) + ChunkPos.y,  3*k );
					glm::vec3 bPos(ChunkPos.x +i ,ChunkPos.y + j,k);
				//	glm::vec3 bPos(ChunkPos.x + i * 2, ChunkPos.y + j * 2, k * 3);
					drawBatch->draw(bPos, glm::vec3(1.0), m_color);
					
				}
			}
		}
	}
}
void Chunk::randActive(int numBlocks)
{
	int numActive = 0;

	if (numBlocks > (CHUNKSIZE * CHUNKSIZE * CHUNKSIZE))
	{
		Debug_Log("Bad input for randActive");
	}
	else
	{
		for (int i = 0; i < CHUNKSIZE * CHUNKSIZE * CHUNKSIZE; i++)
		{
			//if (roll(randEngine) > k +5 && roll(randEngine) > j +1 && roll(randEngine) > i + 3)
			if (randBool(randEngine))
			{
				int x, y, z;
				x = roll(randEngine);
				y = roll(randEngine);
				z = roll(randEngine);
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
	for (int i = 0; i < NUM_CHUNKS; i++)
	{
		delete[] m_chunks[i];
		//m_chunks[i]->dispose();
	}
	delete[] m_chunks;
}

void ChunkManager::update(const glm::vec3 &cameraPos)
{
	glm::vec2 cameraPosXY(cameraPos.x, cameraPos.y);
//	if (cameraPos != lastCameraPos)
	//{
		// TODO: find out where we are

		//cameraPos.x
	Debug_Log(m_chunksDraw);
	m_chunksDraw = 0;
		for (int i = 0; i < NUM_CHUNKS; i++)
		{
			for (int j = 0; j < NUM_CHUNKS; j++)
			{
				glm::vec2 chunkPos(i * CHUNKSIZE,j * CHUNKSIZE);
				glm::vec2 dist = cameraPosXY - chunkPos;
				

				//if (glm::abs(glm::distance(cameraPosXY, chunkPos)) < RENDER_DISTANCE)
				if (glm::length(dist) < RENDER_DISTANCE)
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
					m_chunks[i][j].draw(drawBatch, glm::vec2(i * CHUNKSIZE + i, j * CHUNKSIZE + j));
					m_chunksDraw++;
				}
			}
		}
	}
}
