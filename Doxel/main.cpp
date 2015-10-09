// includes files
#include <gl\glew.h> ///< always include glew before glfw
#include "Window.h"  ///< include after glew, never before. that include glfw too
#include "EasyErrors.h"
#include "InputManager.h"
#include "GLProgram.h"
#include "Camera3D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "FpsCounter.h"
#include "DrawBatch.h"
#include "Block.h"
#include "Light.h"
#include "OBBRayPicking.h"

int main()
{
	auto t_start = std::chrono::high_resolution_clock::now();

	const int width = 1600;
	const int height = 1200;

	if (!glfwInit())
	{
		Debug_Log("Failed to initialize GLFW\n");
	}
	// create a window
	Window m_window;
	m_window.init(width, height, "Doxel");

	// Set up glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Debug_Log("Failed to initialize GLEW\n");
	}

	// Set up the Input Manager
	InputManager m_inputManager;
	m_inputManager.init(m_window.getGlfwWindow());

	glm::vec3 cPos = glm::vec3(-5,3,5);
	Camera3D m_camera;
	m_camera.init(cPos, 45.0f,m_window.getAspectRatio(),1.0, 10000);
	
	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	DrawBatch m_drawBatch;
	m_drawBatch.init(&m_camera);
	

	// compile shaders, add attribes and all that
	GLProgram m_glProgram;
	m_glProgram.loadShaders("Shaders/shader.vert", "Shaders/shader.frag");


	glm::mat4 model, projection, view;
	glm::vec3 mPos(0, 0, 0);

	projection = m_camera.getProjectionMatrix();
	
	FpsCounter m_fpsCounter;
	glm::vec3 lightPos(0, 100, 100);

	//ChunkStuff
	ChunkManager m_chunkManager;
	m_chunkManager.init();

	Light m_light;
	m_light.init(glm::vec3(0, 0, 100), Color3f(1.0,0,0), 1, &m_glProgram);

	m_fpsCounter.start();

	OBBRayPicking rayPicker;
	
	

	std::vector<BlockClicked> m_clickedBlocks;

	// This is the game loop
	while (!m_window.shouldWindowClose())
	{
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_inputManager.update();
		m_camera.update();
		// update input
		// handle input from user
		if (m_inputManager.isKeyPressed(KEYS::ESC))
		{
			m_window.setWindowClose();
		}
		
		if (m_inputManager.isKeyPressed(KEYS::W) || m_inputManager.isKeyHeldDown(KEYS::W)) ///< FORWARD
		{
			m_camera.applyMovement(cMove::Forward);
		}
		if (m_inputManager.isKeyPressed(KEYS::S) || m_inputManager.isKeyHeldDown(KEYS::S)) ///< BACKWARD
		{
			m_camera.applyMovement(cMove::Backward);
		}
		if (m_inputManager.isKeyPressed(KEYS::A) || m_inputManager.isKeyHeldDown(KEYS::A)) ///< LEFT
		{
			m_camera.applyMovement(cMove::Left);
		}
		if (m_inputManager.isKeyPressed(KEYS::D) || m_inputManager.isKeyHeldDown(KEYS::D)) ///< RIGHT
		{
			m_camera.applyMovement(cMove::Right);
		}
		if (m_inputManager.isKeyPressed(KEYS::Z) || m_inputManager.isKeyHeldDown(KEYS::Z)) ///<UP
		{
			m_camera.applyMovement(cMove::Up);
		}
		if (m_inputManager.isKeyPressed(KEYS::X) || m_inputManager.isKeyHeldDown(KEYS::X))///< DOWN
		{
			m_camera.applyMovement(cMove::Down);
		}
		if (m_inputManager.isKeyPressed(KEYS::Q) || m_inputManager.isKeyHeldDown(KEYS::Q))///< rotate left
		{
			m_camera.applyMovement(cMove::Rotate_Left);
		}
		if (m_inputManager.isKeyPressed(KEYS::E) || m_inputManager.isKeyHeldDown(KEYS::E))///< rotate left
		{
			m_camera.applyMovement(cMove::Rotate_Right);
		}
		if (m_inputManager.isKeyPressed(KEYS::F) || m_inputManager.isKeyHeldDown(KEYS::F))///< rotate left
		{
			m_camera.applyMovement(cMove::Roll_Left);
		}
		if (m_inputManager.isKeyPressed(KEYS::G) || m_inputManager.isKeyHeldDown(KEYS::G))///< rotate left
		{
			m_camera.applyMovement(cMove::Roll_Right);
		}
		if (m_inputManager.isKeyPressed(KEYS::C) || m_inputManager.isKeyHeldDown(KEYS::C))///< rotate left
		{
			m_camera.applyMovement(cMove::Pitch_Up);
		}
		if (m_inputManager.isKeyPressed(KEYS::V) || m_inputManager.isKeyHeldDown(KEYS::V))///< rotate left
		{
			m_camera.applyMovement(cMove::Pitch_Down);
		}
		if (m_inputManager.isKeyPressed(KEYS::UP) || m_inputManager.isKeyHeldDown(KEYS::UP))
		{
			m_camera.increaseSpeed();
		}
		if (m_inputManager.isKeyPressed(KEYS::DOWN) || m_inputManager.isKeyHeldDown(KEYS::DOWN))
		{
			m_camera.decreaseSpeed();
		}
		if (m_inputManager.isKeyPressed(KEYS::SPACE))
		{
			m_camera.setPosition(glm::vec3(0)); 
			m_camera.setDirection(glm::vec3(1, 0, 0));
			m_camera.setUpDir(glm::vec3(0, 1, 0));
			m_camera.setSpeed(0.1f);
		}
		if (m_inputManager.isKeyPressed(KEYS::R) || m_inputManager.isKeyHeldDown(KEYS::R))
		{
			m_chunkManager.setGenMethod(GEN_METHOD::RANDOM);
		}
		if (m_inputManager.isKeyPressed(KEYS::T))
		{
			m_chunkManager.setGenMethod(GEN_METHOD::SPHERE);
		}
		if (m_inputManager.isKeyPressed(KEYS::Y))
		{
			m_chunkManager.setGenMethod(GEN_METHOD::ALL);
		}

		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

	
		glm::mat4 view = m_camera.getViewMatrix();
		glm::mat4 mvp = projection * view * model;
		

		if (m_inputManager.isKeyPressed(KEYS::MOUSE_RIGHT))
		{
			if (!m_clickedBlocks.empty())
			{
				m_chunkManager.setBlock(m_clickedBlocks.back(), true);
				m_clickedBlocks.pop_back();
			}
		}
		// ray picking
		if (m_inputManager.isKeyPressed(KEYS::MOUSE_LEFT)){
			bool intersected = false;
			BlockClicked bestCube;
			bestCube.distance = 10000.0f;
			glm::vec3 rayOrigin;
			glm::vec3 rayDirection;
			glm::vec3 aabbMax(BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH);
			glm::vec3 aabbMin(0.0, 0.0, 0.0);
			float distance;
			rayPicker.screenPosToWorldRay(m_inputManager.getCurrentMouseCoords().x, m_window.getHeight() - m_inputManager.getCurrentMouseCoords().y, m_window.getWidth(), m_window.getHeight(), view, projection, rayOrigin, rayDirection);
			bool procced = true;
			// THE SUPER LOOP
			for (unsigned int chunkX = 0; chunkX < NUM_CHUNKS; chunkX++)
			{
				if (!procced)
				{
					break;
				}
				for (unsigned int chunkZ = 0; chunkZ < NUM_CHUNKS; chunkZ++)
				{
					if (!procced)
					{
						break;
					}
					if (!m_chunkManager.getActiveChunk(chunkX, chunkZ))
					{
						continue;
					}
					for (unsigned int blockX = 0; blockX < CHUNK_SIZE; blockX++)
					{
						if (!procced)
						{
							break;
						}
						for (unsigned int blockY = 0; blockY < CHUNK_SIZE; blockY++)
						{
							if (!procced)
							{
								break;
							}
							for (unsigned int blockZ = 0; blockZ < CHUNK_SIZE; blockZ++)
							{
								if (!m_chunkManager.getActiveBlock(chunkX, chunkZ, blockX, blockY, blockZ))
								{
									continue;
								}
								if (!procced)
								{
									break;
								}


								if (rayPicker.testRayOBBIntersection(rayOrigin, rayDirection,
									glm::vec3(chunkX * (CHUNK_SIZE ) + (blockX*BLOCK_WIDTH), (blockY*BLOCK_WIDTH), chunkZ * (CHUNK_SIZE ) + blockZ*BLOCK_WIDTH) + aabbMin,
									glm::vec3(chunkX * (CHUNK_SIZE ) + (blockX*BLOCK_WIDTH), (blockY*BLOCK_WIDTH), chunkZ * (CHUNK_SIZE ) + blockZ*BLOCK_WIDTH) + aabbMax, model,
									glm::vec3(chunkX * (CHUNK_SIZE ) + (blockX*BLOCK_WIDTH), (blockY*BLOCK_WIDTH), chunkZ * (CHUNK_SIZE ) + blockZ*BLOCK_WIDTH), distance))
								{
									/*Debug_Log("INTERSECTION DISTANCE: " << distance);
									Debug_Log("CHUNK IS: " << chunkX << "," << chunkZ);
									Debug_Log("BLOCK IS: " << blockX << "," << blockY << "," << blockZ);
									Debug_Log("");*/
									if (bestCube.distance > distance)
									{
										bestCube.setChunk(chunkX, chunkZ);
										bestCube.setBlock(blockX, blockY, blockZ);
										bestCube.distance = distance; 
										intersected = true;
									}
												//		procced = false;
								}
							}
						}
					}
				}
			}
			if (intersected)
			{
				Debug_Log("CHOSEN");
				Debug_Log("INTERSECTION DISTANCE: " << bestCube.distance);
				Debug_Log("CHUNK IS: " << bestCube.chunkX << "," << bestCube.chunkZ);
				Debug_Log("BLOCK IS: " << bestCube.blockX << "," << bestCube.blockY << "," << bestCube.blockZ);
				m_chunkManager.setBlock(bestCube.chunkX, bestCube.chunkZ, bestCube.blockX, bestCube.blockY, bestCube.blockZ, false);
				m_clickedBlocks.push_back(bestCube);
			}
		}
	//	glm::vec3 lightPos = glm::vec3(cosf(time / 2)* CHUNK_SIZE * NUM_CHUNKS * BLOCK_WIDTH * 1.1, sinf(time / 2) * CHUNK_SIZE * NUM_CHUNKS * BLOCK_WIDTH*1.1, CHUNK_SIZE * NUM_CHUNKS * BLOCK_WIDTH / 2);
		glm::vec3 lightPos(50,50,50);
		m_light.setPosition(lightPos);
		m_glProgram.uploadUniformMatrix("mvp", 1, mvp, GL_FALSE);
		m_glProgram.uploadUniformMatrix("m", 1, model, GL_FALSE);
		m_glProgram.uploadUniformMatrix("v", 1, view, GL_FALSE);
		
		m_light.update();

		m_chunkManager.update(m_camera.getPosition());


		m_drawBatch.start();


		m_chunkManager.draw(&m_drawBatch);
		m_drawBatch.draw(glm::vec3(0, -0.1, 0), glm::vec3((CHUNK_SIZE + 1) * (NUM_CHUNKS), EPSILON * 100, (CHUNK_SIZE + 1) * (NUM_CHUNKS)), Color8(250, 214, 165, 255), true);
	//	m_drawBatch.draw(m_light.getPosition(), glm::vec3(10, 10, 10), Color8(255, 252, 127, 255));
		m_drawBatch.end();
		m_drawBatch.renderBatch();

		// update the window
		m_window.update();

		m_fpsCounter.end();
	}
	m_clickedBlocks.clear();
	//m_chunkManager.dispose(); TODO:FIX
	m_glProgram.deleteProgram();
	
	m_drawBatch.dispose();
	//Close the window 
	m_chunkManager.dispose();
	m_window.dispose();

	glfwTerminate();
	return 0;
}
