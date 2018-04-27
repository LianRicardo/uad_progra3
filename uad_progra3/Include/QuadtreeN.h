#pragma once
#include "..\Include\Quadtree.h"

class QuadtreeN
{
private:
	CVector3 info;
	QuadtreeN *tl;
	QuadtreeN *tr;
	QuadtreeN *dl;
	QuadtreeN *dr;
	CVector3 center;
public:
	QuadtreeN(CVector3* verticesNode, CGameGrid* pgrid);
	~QuadtreeN();
	void dividir(CGameGrid* pgrid);
};