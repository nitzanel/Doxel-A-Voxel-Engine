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

	glm::vec3 cPos = glm::vec3(0);
	Camera3D m_camera;
	m_camera.init(cPos, 45.0f,m_window.getAspectRatio(),1.0, 10000);
	
	
	glEnable(GL_DEPTH_TEST);
	

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

	m_fpsCounter.start();


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
			m_camera.setDirection(glm::vec3(1, 1, 0));
			m_camera.setUpDir(glm::vec3(0, 0, 1));
			m_camera.setSpeed(0.1f);
		}
		if (m_inputManager.isKeyPressed(KEYS::T))
		{
			m_chunkManager.setGenMethod(GEN_METHOD::SPHERE);
		}
		if (m_inputManager.isKeyPressed(KEYS::R))
		{
			m_chunkManager.setGenMethod(GEN_METHOD::RANDOM);
		}
		if (m_inputManager.isKeyPressed(KEYS::Y))
		{
			m_chunkManager.setGenMethod(GEN_METHOD::ALL);
		}

		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();



		// Use the glProgram
//		m_glProgram.use();
		// UPLOAD THE CAMERA MATRIX AFTER YOU CALLED THE PROGRAM.
//		m_glProgram.uploadUnifromMatrix("view", 1, view, GL_FALSE);
//		m_glProgram.uploadUnifromMatrix("model", 1, model, GL_FALSE);

		glm::mat4 view = m_camera.getViewMatrix();
		glm::mat4 mvp = projection * view * model;

		glm::vec3 lightPos = glm::vec3(cosf(time / 2)* 100,0,sinf(time / 2)* 100);
		//m_camera.setPosition(lightPos);
	//	glm::vec3 lightPos = m_camera.getPosition() + glm::vec3(0, 0, 50);
		m_glProgram.uploadUniformMatrix("mvp", 1, mvp, GL_FALSE);
		m_glProgram.uploadUniformMatrix("m", 1, model, GL_FALSE);
		m_glProgram.uploadUniformMatrix("v", 1, view, GL_FALSE);
		m_glProgram.uploadUniformVector3("lightPosition_worldSpace", 1, lightPos);

		m_chunkManager.update(m_camera.getPosition());


		m_drawBatch.start();


		m_chunkManager.draw(&m_drawBatch);
		m_drawBatch.draw(glm::vec3(0, 0, -0.1), glm::vec3(CHUNK_SIZE * NUM_CHUNKS, CHUNK_SIZE * NUM_CHUNKS, EPSILON), Color8(255, 255, 255, 255), true);
		m_drawBatch.draw(lightPos, glm::vec3(10, 10, 10), Color8(255, 255, 255, 255));
		m_drawBatch.end();
		m_drawBatch.renderBatch();
		
	

	
		

		// update the window
		m_window.update();

		m_fpsCounter.end();
	}
	//m_debugRenderer.dispose();
	//m_chunkManager.dispose();
	m_glProgram.deleteProgram();
	
	m_drawBatch.dispose();
	//Close the window 
	m_chunkManager.dispose();
	m_window.dispose();

	glfwTerminate();
	return 0;
}
