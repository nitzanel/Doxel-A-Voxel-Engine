#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

const float PI = 3.141592f;

enum cMove
{
	Forward, Backward, Left, Right, Up, Down, Rotate_Left, Rotate_Right, Roll_Right, Roll_Left, Pitch_Up, Pitch_Down
};

class Camera3D
{
public:
	Camera3D();
	~Camera3D();

	void init(glm::vec3 position, float fov, float aspectRatio, float near, float far);

	void update();
	void applyMovement(cMove cmove);

	void increaseSpeed() { SPEED_FACTOR += 1; }
	void decreaseSpeed() { if(SPEED_FACTOR > 1) SPEED_FACTOR -= 1; }

	//Culling
	bool inFrame(glm::vec3 position);
	void getFrustum();


	// Getters
	const glm::mat4 getViewMatrix()  { return m_view; }
	const glm::mat4 getProjectionMatrix()  { return m_projection; }
	const glm::vec3 getPosition() { return m_position; }

	// setters
	void setPosition(glm::vec3 pos) { m_position = pos; }
	void setDirection(glm::vec3 dir) { m_direction = glm::normalize(dir);}
	void setSpeed(float speed) { SPEED_FACTOR = speed; }
	void setUpDir(glm::vec3 up) { m_upVec = glm::normalize(up); }
private:

	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::vec3 m_position;
	glm::vec3 m_upVec = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 m_direction = glm::normalize(glm::vec3(1.0f, 1.0f, 0));

	glm::mat4 proj, vie, clip;
	float frustum[6][4];
	float t;

	float m_angleRot = glm::radians(1.0f);

	float m_fov, m_aspectRatio, m_near, m_far, SPEED_FACTOR  = 0.1f;
	
};

