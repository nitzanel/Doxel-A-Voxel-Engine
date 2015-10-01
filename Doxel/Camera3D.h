#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

const float PI = 3.141592f;
/*
defines camera movement and rotation
*/
enum cMove
{
	Forward, Backward, Left, Right, Up, Down, Rotate_Left, Rotate_Right, Roll_Right, Roll_Left, Pitch_Up, Pitch_Down
};

class Camera3D
{
public:
	/*
	Create a camera3D object.
	*/
	Camera3D();
	/*
	Destroy a camera3D object.
	*/
	~Camera3D();
	/*
	This function initialize the camera object.
	Input: 
		- glm::vec3 position - the starting position of the camera, in in-world coordinations.
		- float fov - the field of view of the camera. in a range of 0 to 90.
		- float aspectRatio - the aspect ratio of the camera. usually the widht/height of the window.
		- float near - the minimun distance from the camera that an object must be from, to be in the frustum.
		- float far - the maximun distance from the camera that an object can be from the camera and be in the frustum.
	*/
	void init(glm::vec3 position, float fov, float aspectRatio, float near, float far);
	/*
	This function updates the camera.
	Should be called before rendering any frame and after recieving input (?).
	*/
	void update();
	/*
	This function will move the camera or rotate it according to the cMove input.
	Input:
		- cMove cmove - the camera will move or rotate according to the value of cmove.
	*/
	void applyMovement(cMove cmove);
	/*
	This function increases the movement speed of the camera.
	*/
	void increaseSpeed() { SPEED_FACTOR += 0.1;}
	/*
	This function decreases the movement speed of the camera.
	*/
	void decreaseSpeed() { if(SPEED_FACTOR > 0.1) SPEED_FACTOR -= 0.1; }

	//Culling
	/*
	This function  checks if a specific point is in the camera frame.
	Input:
		- glm::vec3 position - the position of the point.
	Output:
		- bool - will return true if the point is in the frame, otherwise will return false.
	*/
	bool inFrame(glm::vec3 position);
	/*
	This function will update the camera frustum.
	Should be called before checking if a point is in the frustum.
	Note: is called in DrawBatch::start.
	*/
	void getFrustum();


	// Getters
	/*
	This function returns the view matrix.
	*/
	const glm::mat4 getViewMatrix()  { return m_view; }
	/*
	This function returns the projection matrix.
	*/
	const glm::mat4 getProjectionMatrix()  { return m_projection; }
	/*
	this function return the position of the camera.
	*/
	const glm::vec3 getPosition() { return m_position; }

	// setters
	/*
	This functions sets the camera position.
	Input:
		- glm::vec3 pos - the new position of the camera.
	*/
	void setPosition(glm::vec3 pos) { m_position = pos; }
	/*
	This functions sets the camera direction.
	Input:
	- glm::vec3 dir - the new direction of the camera.
	*/
	void setDirection(glm::vec3 dir) { m_direction = glm::normalize(dir);}
	/*
	This functions sets the up direction of the camera.
	Input:
	- glm::vec3 up - the new up direction of the camera.
	*/
	void setUpDir(glm::vec3 up) { m_upVec = glm::normalize(up); }
	/*
	This functions sets the camera speed.
	Input:
	- float speed - the new speed of the camera.
	*/
	void setSpeed(float speed) { SPEED_FACTOR = speed; }
	
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

