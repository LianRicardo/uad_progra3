#pragma once

#include "CGameGrid.h"
#include "COpenGLRenderer.h"
#include "CHex.h"

class CWorld
{
private:
	void save();
	void load();
	unsigned int sid;
public:
	bool inicializado;
	CGameGrid *gamegrid;
	COpenGLRenderer * const r;
	void render();
	bool init();
	CWorld(COpenGLRenderer *r);
	~CWorld();
	float* getvertex();
	size_t getn_vertex();
	unsigned short* getvertexindex();
	size_t getn_vertexindex();
};