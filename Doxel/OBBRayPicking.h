#pragma once
#include <glm\glm.hpp>

class OBBRayPicking
{
public:
	OBBRayPicking();
	~OBBRayPicking();
	/*
	Input:
		-glm::vec3 ray_origin -			Ray origin, in world space Ray origin, in world space
		-glm::vec3 ray_direction-		Ray direction (NOT target position!), in world space. Must be normalize()'d.
		-glm::vec3 aabb_min-			Minimum X,Y,Z coords of the mesh when not transformed at all.
		-glm::vec3 aabb_max-			Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
		-glm::mat4 modelMatrix-			Transformation applied to the mesh (which will thus be also applied to its bounding box)
		-float& intersection_distance-  Output : distance between ray_origin and the intersection with the OBB
	output:
		bool - true if intersects.
	*/
	bool testRayOBBIntersection(
		glm::vec3 ray_origin,        // Ray origin, in world space
		glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
		glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
		glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
		const glm::mat4 &modelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
		const glm::vec3 &position, // the position because model matrix doesnt do anything in this game
		float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
		);
	/*
	Input:
		-int mouseX, int mouseY-             Mouse position, in pixels, from bottom-left corner of the window
		-int screenWidth, int screenHeight-  Window size, in pixels
		-glm::mat4 viewMatrix-               Camera position and orientation
		-glm::mat4 projectionMatrix-         Camera parameters (ratio, field of view, near and far planes)
		-glm::vec3& out_origin-              Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
		-glm::vec3& out_direction-           Ouput : Direction, in world space, of the ray that goes "through" the mouse.
	
	*/
	void screenPosToWorldRay(
		int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
		int screenWidth, int screenHeight,  // Window size, in pixels
		const glm::mat4 &viewMatrix,               // Camera position and orientation
		const glm::mat4 &projectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
		glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
		glm::vec3& out_direction       // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
		);
};

