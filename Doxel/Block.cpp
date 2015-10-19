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
		shouldUpdate = true;
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
	Color8 colors[] {Color8(102, 51, 0, 255), Color8(124, 252, 0, 255) };
	

	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{

			for (int k = 0; k < CHUNK_SIZE; k++)
			{	
					bool shouldDraw = true;
					Color8 blockColor = colors[0];
					//	bool isGrass = false;

					if (!m_blocks[i][j][k].getActive())
					{
						shouldDraw = false;
					}
					bool jPositive = false;
					if (shouldDraw)
					{
						bool iNegative = false;
						if (i > 0)
							iNegative = m_blocks[i - 1][j][k].getActive();

						bool iPositive = false;
						if (i < CHUNK_SIZE - 1)
							iPositive = m_blocks[i + 1][j][k].getActive();
						bool jNegative = false;
						if (j > 0)
							jNegative = m_blocks[i][j - 1][k].getActive();
						if (j < CHUNK_SIZE - 1)
							jPositive = m_blocks[i][j + 1][k].getActive();

						bool kNegative = false;
						if (k > 0)
							kNegative = m_blocks[i][j][k - 1].getActive();

						bool kPositive = false;
						if (k < CHUNK_SIZE - 1)
							kPositive = m_blocks[i][j][k + 1].getActive();
						if (iNegative && iPositive && jNegative &&jPositive && kNegative && kPositive)
						{
							shouldDraw = false;
						}

						if (!jPositive)
						{
							blockColor = colors[1];

						}
						
					}
					if (rows.empty())
					{
						rows.emplace_back(k, k, blockColor,shouldDraw);
					}
					else
					{
						
						if ((!rows.back().color.isEquals(blockColor)) || (rows.back().shouldbeDrawn!= shouldDraw))
						{
							rows.emplace_back(k, k, blockColor, shouldDraw);
						}
						else
						{
							rows.back().end = k;
						}
					}
				
					
				
				
			
			}
			for (int index = 0; index < rows.size(); index++)
			{
				rows[index].Update();
				//Debug_Log("position of the row is" << i << "," << j << "," << (int)rows[index].start << "," << (int)rows[index].end<<"  should be drawn "<<rows[index].shouldbeDrawn);
				if (rows[index].shouldbeDrawn)
				{
					glm::vec3 rowStart(ChunkPos.x + i, j, ChunkPos.y + rows[index].start);
					glm::vec3 scale(BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH*rows[index].length);					
					drawBatch->draw(rowStart, scale, rows[index].color);				
				}

			}
			rows.clear();
		}
	}
}
void Chunk::draw(DrawBatch* drawBatch, glm::vec2 &ChunkPos, BlockClicked &currentBlock)
{
	Color8 colors[] {Color8(102, 51, 0, 255), Color8(124, 252, 0, 255),Color8(255,255,255,255) };


	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{

			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				bool shouldDraw = true;
				Color8 blockColor = colors[0];
				//	bool isGrass = false;

				if (!m_blocks[i][j][k].getActive())
				{
					shouldDraw = false;
				}
				bool jPositive = false;
				if (shouldDraw)
				{
					bool iNegative = false;
					if (i > 0)
						iNegative = m_blocks[i - 1][j][k].getActive();

					bool iPositive = false;
					if (i < CHUNK_SIZE - 1)
						iPositive = m_blocks[i + 1][j][k].getActive();
					bool jNegative = false;
					if (j > 0)
						jNegative = m_blocks[i][j - 1][k].getActive();
					if (j < CHUNK_SIZE - 1)
						jPositive = m_blocks[i][j + 1][k].getActive();

					bool kNegative = false;
					if (k > 0)
						kNegative = m_blocks[i][j][k - 1].getActive();

					bool kPositive = false;
					if (k < CHUNK_SIZE - 1)
						kPositive = m_blocks[i][j][k + 1].getActive();
					if (iNegative && iPositive && jNegative &&jPositive && kNegative && kPositive)
					{
						shouldDraw = false;
					}

					if (!jPositive)
					{
						blockColor = colors[1];

					}
					if ((currentBlock.blockX == i) && (currentBlock.blockY == j) && (currentBlock.blockZ == k))
					{
						blockColor = colors[2];
					}

				}
				if (rows.empty())
				{
					rows.emplace_back(k, k, blockColor, shouldDraw);
				}
				else
				{

					if ((!rows.back().color.isEquals(blockColor)) || (rows.back().shouldbeDrawn != shouldDraw))
					{
						rows.emplace_back(k, k, blockColor, shouldDraw);
					}
					else
					{
						rows.back().end = k;
					}
				}





			}
			for (int index = 0; index < rows.size(); index++)
			{
				rows[index].Update();
				//Debug_Log("position of the row is" << i << "," << j << "," << (int)rows[index].start << "," << (int)rows[index].end<<"  should be drawn "<<rows[index].shouldbeDrawn);
				if (rows[index].shouldbeDrawn)
				{
					glm::vec3 rowStart(ChunkPos.x + i, j, ChunkPos.y + rows[index].start);
					glm::vec3 scale(BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH*rows[index].length);
					drawBatch->draw(rowStart, scale, rows[index].color);
				}

			}
			rows.clear();
		}
	}
}

void Chunk::draw(Renderer* renderer, glm::vec2 &ChunkPos)
{
	Color8 colors[] {Color8(102, 51, 0, 255), Color8(124, 252, 0, 255) };
//	Debug_Log("Chunk is drawing");


	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{

			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				bool shouldDraw = true;
				Color8 blockColor = colors[0];
				//	bool isGrass = false;

				if (!m_blocks[i][j][k].getActive())
				{
					shouldDraw = false;
				}
				bool jPositive = false;
				if (shouldDraw)
				{
					bool iNegative = false;
					if (i > 0)
						iNegative = m_blocks[i - 1][j][k].getActive();

					bool iPositive = false;
					if (i < CHUNK_SIZE - 1)
						iPositive = m_blocks[i + 1][j][k].getActive();
					bool jNegative = false;
					if (j > 0)
						jNegative = m_blocks[i][j - 1][k].getActive();
					if (j < CHUNK_SIZE - 1)
						jPositive = m_blocks[i][j + 1][k].getActive();

					bool kNegative = false;
					if (k > 0)
						kNegative = m_blocks[i][j][k - 1].getActive();

					bool kPositive = false;
					if (k < CHUNK_SIZE - 1)
						kPositive = m_blocks[i][j][k + 1].getActive();
					if (iNegative && iPositive && jNegative &&jPositive && kNegative && kPositive)
					{
						shouldDraw = false;
					}

					if (!jPositive)
					{
						blockColor = colors[1];

					}

				}
				if (rows.empty())
				{
					rows.emplace_back(k, k, blockColor, shouldDraw);
				}
				else
				{

					if ((!rows.back().color.isEquals(blockColor)) || (rows.back().shouldbeDrawn != shouldDraw))
					{
						rows.emplace_back(k, k, blockColor, shouldDraw);
					}
					else
					{
						rows.back().end = k;
					}
				}





			}

			for (int index = 0; index < rows.size(); index++)
			{
				rows[index].Update();
				//Debug_Log("position of the row is" << i << "," << j << "," << (int)rows[index].start << "," << (int)rows[index].end<<"  should be drawn "<<rows[index].shouldbeDrawn);
				if (rows[index].shouldbeDrawn)
				{
					glm::vec3 rowStart(ChunkPos.x + i, j, ChunkPos.y + rows[index].start);
					glm::vec3 scale(BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH*rows[index].length);
					renderer->draw(rowStart, scale, rows[index].color);
				}

			}
			rows.clear();
		}
	}
}
void Chunk::draw(Renderer* renderer, glm::vec2 &ChunkPos, BlockClicked &currentBlock)
{
	Color8 colors[] {Color8(102, 51, 0, 255), Color8(124, 252, 0, 255), Color8(255, 255, 255, 255) };

	//Debug_Log("Chunk is drawing");

	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{

			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				bool shouldDraw = true;
				Color8 blockColor = colors[0];
				//	bool isGrass = false;

				if (!m_blocks[i][j][k].getActive())
				{
					shouldDraw = false;
				}
				bool jPositive = false;
				if (shouldDraw)
				{
					bool iNegative = false;
					if (i > 0)
						iNegative = m_blocks[i - 1][j][k].getActive();

					bool iPositive = false;
					if (i < CHUNK_SIZE - 1)
						iPositive = m_blocks[i + 1][j][k].getActive();
					bool jNegative = false;
					if (j > 0)
						jNegative = m_blocks[i][j - 1][k].getActive();
					if (j < CHUNK_SIZE - 1)
						jPositive = m_blocks[i][j + 1][k].getActive();

					bool kNegative = false;
					if (k > 0)
						kNegative = m_blocks[i][j][k - 1].getActive();

					bool kPositive = false;
					if (k < CHUNK_SIZE - 1)
						kPositive = m_blocks[i][j][k + 1].getActive();
					if (iNegative && iPositive && jNegative &&jPositive && kNegative && kPositive)
					{
						shouldDraw = false;
					}

					if (!jPositive)
					{
						blockColor = colors[1];

					}
					if ((currentBlock.blockX == i) && (currentBlock.blockY == j) && (currentBlock.blockZ == k))
					{
						blockColor = colors[2];
					}

				}
				if (rows.empty())
				{
					rows.emplace_back(k, k, blockColor, shouldDraw);
				}
				else
				{

					if ((!rows.back().color.isEquals(blockColor)) || (rows.back().shouldbeDrawn != shouldDraw))
					{
						rows.emplace_back(k, k, blockColor, shouldDraw);
					}
					else
					{
						rows.back().end = k;
					}
				}





			}
			for (int index = 0; index < rows.size(); index++)
			{
				rows[index].Update();
				//Debug_Log("position of the row is" << i << "," << j << "," << (int)rows[index].start << "," << (int)rows[index].end<<"  should be drawn "<<rows[index].shouldbeDrawn);
				if (rows[index].shouldbeDrawn)
				{
					glm::vec3 rowStart(ChunkPos.x + i, j, ChunkPos.y + rows[index].start);
					glm::vec3 scale(BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH*rows[index].length);
					renderer->draw(rowStart, scale, rows[index].color);
				}

			}
			rows.clear();
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
	}
}

ChunkManager::~ChunkManager()
{
	delete[] m_chunks;
	m_chunks = nullptr;
}

void ChunkManager::update(const glm::vec3 &cameraPos)
{
	glm::vec2 cameraPosXZ(cameraPos.x, cameraPos.z);

	//Debug_Log(m_chunksDraw);
	m_chunksDraw = 0;
	
	for (int i = 0; i < NUM_CHUNKS; i++)
		{
			for (int j = 0; j < NUM_CHUNKS; j++)
			{
				glm::vec2 chunkPos(i * CHUNK_SIZE * BLOCK_WIDTH, j * CHUNK_SIZE * BLOCK_WIDTH);
				glm::vec2 dist = cameraPosXZ - chunkPos;
				
				if (glm::abs(glm::length(dist)) < RENDER_DISTANCE)
				{	
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
					if (m_currentClicked.chunkX == i && m_currentClicked.chunkZ == j)
					{
						m_chunks[i][j].draw(drawBatch, glm::vec2(i * CHUNK_SIZE, j * CHUNK_SIZE), m_currentClicked);
					}
					else
					{
						m_chunks[i][j].draw(drawBatch, glm::vec2(i * CHUNK_SIZE, j * CHUNK_SIZE));
					}
					m_chunksDraw++;
				}
			}
		}
	}
}

void ChunkManager::draw(Renderer* renderer)
{
	for (int i = 0; i < NUM_CHUNKS; i++)
	{
		for (int j = 0; j < NUM_CHUNKS; j++)
		{
			if (m_chunks[i][j].isActive)
			{
				if (m_chunks[i][j].isInit)
				{
					if (m_currentClicked.chunkX == i && m_currentClicked.chunkZ == j)
					{
						m_chunks[i][j].draw(renderer, glm::vec2(i * CHUNK_SIZE, j * CHUNK_SIZE), m_currentClicked);
					}
					else
					{
						m_chunks[i][j].draw(renderer, glm::vec2(i * CHUNK_SIZE, j * CHUNK_SIZE));
					}
					m_chunksDraw++;
				}
			}
		}
	}
}
