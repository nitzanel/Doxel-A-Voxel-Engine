#include "Camera3D.h"

float Rotation_Factor = 1.0f;
Camera3D::Camera3D()
{
}


Camera3D::~Camera3D()
{
}

void Camera3D::init(glm::vec3 position, float fov, float aspectRatio, float near, float far)
{
	m_position = position;
	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_near = near;
	m_far = far;
	SPEED_FACTOR = 0.1f;
	m_projection = glm::perspective(glm::radians(m_fov), (float)1.5/m_aspectRatio, m_near, m_far);
}

void Camera3D::update()
{
	m_view = glm::lookAt(m_position, m_position + m_direction, m_upVec);
}

void Camera3D::applyMovement(cMove cmove) ///< FIXED :D
{
	switch (cmove)
	{
	case Forward:
		m_position += glm::normalize(m_direction) * SPEED_FACTOR;
		break;
	case Backward:
		m_position -= glm::normalize(m_direction) * SPEED_FACTOR;
		break;
	case Left:
		m_position -= glm::normalize(glm::cross(m_direction, m_upVec)) * SPEED_FACTOR;
		break;
	case Right:
		m_position += glm::normalize(glm::cross(m_direction, m_upVec)) * SPEED_FACTOR;
		break;
	case Up:
		m_position += m_upVec * SPEED_FACTOR;
		break;
	case Down:
		m_position -= m_upVec * SPEED_FACTOR;
		break;
	case Rotate_Left:
		m_direction = glm::rotate(m_direction, m_angleRot * Rotation_Factor, m_upVec);
		break;
	case Rotate_Right:
		m_direction = glm::rotate(m_direction, -m_angleRot * Rotation_Factor, m_upVec);
		break;
	case Roll_Left:
		m_upVec = glm::rotate(m_upVec, -m_angleRot * Rotation_Factor, m_direction);
		break;
	case Roll_Right:
		m_upVec = glm::rotate(m_upVec, m_angleRot * Rotation_Factor, m_direction);
		break;
	case Pitch_Up:
		m_direction = glm::rotate(m_direction, m_angleRot * Rotation_Factor, glm::cross(m_direction, m_upVec));
		m_upVec = glm::rotate(m_upVec, m_angleRot, glm::cross(m_direction, m_upVec));
		break;
	case Pitch_Down:
		m_direction = glm::rotate(m_direction, -m_angleRot * Rotation_Factor, glm::cross(m_direction, m_upVec));
		m_upVec = glm::rotate(m_upVec, -m_angleRot, glm::cross(m_direction, m_upVec));
		break;
	default:
		break;
	}
}

bool Camera3D::inFrame(glm::vec3 position)
{
	// Frustum code taken from http://www.crownandcutlass.com/features/technicaldetails/frustum.html.
	// and modified by Nitzan Elbaz to work with glm.
	for (int p = 0; p < 6; p++)
	{
		if (frustum[p][0] * position.x + frustum[p][1] * position.y + frustum[p][2] * position.z + frustum[p][3] <= -2)
			return false;
	}
	return true;
}

void Camera3D::getFrustum()
{
	// Frustum code taken from http://www.crownandcutlass.com/features/technicaldetails/frustum.html.
	// and modified by Nitzan Elbaz to work with glm.

	vie = getViewMatrix();
	proj = getProjectionMatrix();

	clip = proj * vie;

	/* Extract the numbers for the RIGHT plane */
	frustum[0][0] = clip[0][3] - clip[0][0];
	frustum[0][1] = clip[1][3] - clip[1][0];
	frustum[0][2] = clip[2][3] - clip[2][0];
	frustum[0][3] = clip[3][3] - clip[3][0];

	/* Normalize the result */
	t = sqrt(frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2]);
	frustum[0][0] /= t;
	frustum[0][1] /= t;
	frustum[0][2] /= t;
	frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	frustum[1][0] = clip[0][3] + clip[0][0];
	frustum[1][1] = clip[1][3] + clip[1][0];
	frustum[1][2] = clip[2][3] + clip[2][0];
	frustum[1][3] = clip[3][3] + clip[3][0];

	/* Normalize the result */
	t = sqrt(frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2]);
	frustum[1][0] /= t;
	frustum[1][1] /= t;
	frustum[1][2] /= t;
	frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	frustum[2][0] = clip[0][3] + clip[0][1];
	frustum[2][1] = clip[1][3] + clip[1][1];
	frustum[2][2] = clip[2][3] + clip[2][1];
	frustum[2][3] = clip[3][3] + clip[3][1];

	/* Normalize the result */
	t = sqrt(frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2]);
	frustum[2][0] /= t;
	frustum[2][1] /= t;
	frustum[2][2] /= t;
	frustum[2][3] /= t;

	/* Extract the TOP plane */
	frustum[3][0] = clip[0][3] - clip[0][1];
	frustum[3][1] = clip[1][3] - clip[1][1];
	frustum[3][2] = clip[2][3] - clip[2][1];
	frustum[3][3] = clip[3][3] - clip[3][1];


	/* Normalize the result */
	t = sqrt(frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2]);
	frustum[3][0] /= t;
	frustum[3][1] /= t;
	frustum[3][2] /= t;
	frustum[3][3] /= t;


	/* Extract the FAR plane */
	frustum[4][0] = clip[0][3] - clip[0][2];
	frustum[4][1] = clip[1][3] - clip[1][2];
	frustum[4][2] = clip[2][3] - clip[2][2];
	frustum[4][3] = clip[3][3] - clip[3][2];

	/* Normalize the result */
	t = sqrt(frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2]);
	frustum[4][0] /= t;
	frustum[4][1] /= t;
	frustum[4][2] /= t;
	frustum[4][3] /= t;

	/* Extract the NEAR plane */
	frustum[5][0] = clip[0][3] + clip[0][2];
	frustum[5][1] = clip[1][3] + clip[1][2];
	frustum[5][2] = clip[2][3] + clip[2][2];
	frustum[5][3] = clip[3][3] + clip[3][2];

	/* Normalize the result */
	t = sqrt(frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2]);
	frustum[5][0] /= t;
	frustum[5][1] /= t;
	frustum[5][2] /= t;
	frustum[5][3] /= t;

}