#pragma once
#include "Renderer.h"
#include "Doxel.h"

class DebugRenderer : public Renderer
{
public:
	DebugRenderer();
	~DebugRenderer();

protected:
	/*
	Create the render batches.
	Fills a vector of vertecies with the vertex data, and uploads it to a buffer.
	Fills a vector of indecies with the indecies data, and uploads it to a buffer.
	is a pure virtual function.
	*/
	virtual void createRenderBatches();

};

