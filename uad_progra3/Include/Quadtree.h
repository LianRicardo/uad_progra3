#pragma once

#include <iostream>
#include "../Include/CVector3.h"
#include "../Include/CGameGrid.h"
#include "../Include/QuadtreeN.h"

class Quadtree
{
private:
	CGameGrid * pgrid;
	CVector3 VertexR[2];
public:
	Quadtree(CGameGrid *pgrid);
	~Quadtree();
	CVector3* getVertexR();
	bool Inicializarq();
};