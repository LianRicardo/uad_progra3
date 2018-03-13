#pragma once

#include "CGameGrid.h"
#include "COpenGLRenderer.h"
#include "CHex.h"

class CWorld
{
private:
	void save();
	void load();
public:
	CGameGrid gamegrid;
	COpenGLRenderer* r;
	void render();
	bool init();
	CWorld();
	~CWorld();
	float* getvertex();
	size_t getn_vertex();
	unsigned short* getvertexindex();
	size_t getn_vertexindex();
};