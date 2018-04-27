#pragma once

#include "CGameGrid.h"
#include "COpenGLRenderer.h"
#include "CHex.h"
#include "Quadtree.h"

class CWorld
{
private:
	void save();
	void load();
	vector<string> m_TextureNames;
	vector<unsigned int> m_TexturesID;
	unsigned int sid;
	vector<string> texturename;
	unsigned int texture_id;
public:
	bool inicializarqt();
	bool inicializado;
	CGameGrid *gamegrid;
	Quadtree *qt;
	COpenGLRenderer * const r;
	void render(CVector3 cpos);
	bool init();
	CWorld(COpenGLRenderer *r);
	~CWorld();
	float* getvertex();
	size_t getn_vertex();
	unsigned short* getvertexindex();
	size_t getn_vertexindex();
};