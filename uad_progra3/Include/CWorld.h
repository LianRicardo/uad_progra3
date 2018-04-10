#pragma once

#include "CGameGrid.h"
#include "COpenGLRenderer.h"
#include "CHex.h"
#include "CApp.h"

class CWorld
{
private:
	void save();
	void load();

public:
	bool inicializado;
	CGameGrid gamegrid;
	COpenGLRenderer * const r;
	void render();
	bool init();
	CWorld(COpenGLRenderer *r);
	CWorld();
	~CWorld();
	float* getvertex();
	size_t getn_vertex();
	unsigned short* getvertexindex();
	size_t getn_vertexindex();
};