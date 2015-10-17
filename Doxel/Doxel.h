#pragma once

#define BLOCK_WIDTH 1
#define CHUNK_SIZE  64
#define NUM_CHUNKS 4

#define RENDER_DISTANCE 200.0f

#define EPSILON 0.001
#define PI 3.141592f

#define DEFAULT_TITLE "Doxel Engine"

#define NUM_OF_VERTECIES_IN_AN_ARC 8
#define NUM_OF_VERTECIES_IN_A_DOUBLE_COLOR_ARC 12
#define NUM_OF_NORMALS_IN_AN_ARC 6
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
