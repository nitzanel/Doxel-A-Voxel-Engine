#pragma once
#include "EasyErrors.h"

#define BLOCK_WIDTH 1
#define CHUNK_SIZE  8
#define NUM_CHUNKS 1

#define RENDER_DISTANCE 200.0f

#define EPSILON 0.001
#define PI 3.141592f

#define DEFAULT_TITLE "Doxel Engine"

#define NUM_OF_VERTECIES_IN_AN_ARC 8
#define NUM_OF_VERTECIES_IN_A_DOUBLE_COLOR_ARC 12
#define NUM_OF_INDECIES_IN_AN_ARC 36
#define NUM_OF_NORMALS_IN_AN_ARC 6
#define NUM_OF_LINES_IN_AN_ARC 12
#define NUM_OF_VERTECIES_IN_LINED_ARC 24
/*
The offset when sending indecies to the buffer 
*/
#define TWO_COLOR_ARC_VERTECIES_OFFSET_OF_ONE_COLOR_ARC 4
/*
The number of vertecies in a glyph object.
*/
#define NUMBER_OF_VERTS_IN_GLYPH 8
/*
the number of indecies there are in a cube.
*/
#define NUMBER_OF_INDECIES_IN_A_CUBE 36
/*
the number of normal vectors in a cube. one for each face.
*/
#define NUMBER_OF_NORMALS_IN_A_CUBE 6


typedef unsigned char byte;
typedef unsigned int uint;