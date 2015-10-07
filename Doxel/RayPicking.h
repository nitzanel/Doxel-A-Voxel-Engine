#pragma once

#include <glm\glm.hpp>
#include "InputManager.h"

void sceenPosToWorldRay(int mouseX, int mouseY,				// Mouse position, in pixels, from bottom-left corner of the window
						int screenWidth, int screenHeight,  // Window size, in pixels
						const glm::mat4 &viewMatrix,        // Camera position and orientation
						const glm::mat4 &projectionMatrix,  // Camera parameters (ratio, field of view, near and far planes)
						glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
						glm::vec3& out_direction			// Ouput : Direction, in world space, of the ray that goes "through" the mouse.
						)
{
	float x = (2.0f * mouseX) / screenWidth - 1.0f;
	float y = 1.0 - (2.0 * mouseY) / screenHeight;
	float z = 1.0f;
	//Step 1: 3d Normalised Device Coordinates
	glm::vec3 rayNDS = glm::vec3(x, y, z); ///< NDS = normalized device coordinates
	//Step 2: 4d Homogeneous Clip Coordinates
	glm::vec4 rayClip = glm::vec4(rayNDS.x, rayNDS.y, -1.0, 1.0);
	//Step 3: 4d Eye (Camera) Coordinates
	glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
	rayEye.z = -1.0;
	rayEye.w = 0.0;
	//Step 4: 4d World Coordinates
	glm::vec4 rayWorld_4 = glm::inverse(viewMatrix) * rayEye;
	glm::vec3 rayWord = glm::normalize(glm::vec3(rayWorld_4.x, rayWorld_4.y, rayWorld_4.z));


}