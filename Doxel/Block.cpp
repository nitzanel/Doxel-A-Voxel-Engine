#include "Block.h"
#include "EasyErrors.h"
#include <ctime>
const float RENDER_DISTANCE = 100.0f;

std::mt19937 randEngine(time(NULL));
std::uniform_int_distribution<int> distribution(0, 255);

Block::Block()
{
}


Block::~Block()
{
}


Chunk::Chunk()
{
	int R = distribution(randEngine);
	int G = distribution(randEngine);
	int B = distribution(randEngine);
	m_color = Color8(R, G, B, 255);

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
}
void Chunk::init()
{
	
}
Chunk::~Chunk()
{
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
void Chunk::update()
{
	if (shouldUpdate)
	{
		for (int i = 0; i < CHUNKSIZE; i++)
		{
			for (int j = 0; j < CHUNKSIZE; j++)
			{
				for (int k = 0; k < CHUNKSIZE; k++)
				{
					m_blocks[i][j]->setActive(isActive);
				}

			}
		}
		shouldUpdate = false;
	}

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
					glm::vec3 bPos(ChunkPos.x +  sinf(i * j) * i, j * cosf(j) + ChunkPos.y,  3*k );
				//	glm::vec3 bPos(ChunkPos.x + i * 2, ChunkPos.y + j * 2, k * 3);
					drawBatch->draw(bPos, glm::vec3(1.0), m_color);
					
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
					m_chunks[i][j].setActive(true);
					m_chunks[i][j].update();
				}
				else
				{
					m_chunks[i][j].setActive(false);
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
				m_chunks[i][j].draw(drawBatch, glm::vec2(i * CHUNKSIZE + i, j * CHUNKSIZE + j));
				m_chunksDraw++;
			}
		}
	}
}
