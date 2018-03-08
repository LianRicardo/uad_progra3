#pragma once

#include "CHex.h"
#include "CVector3.h"


class CGameGrid
{
	CHex grid[100][100];
	CVector3 vindices[12];
	bool inicializar(CVector3 v[6], CVector3 pos, CVector3 center, CVector3 centerx, CVector3 centery, CVector3 vindices[3], CVector3 vindices1[3], CVector3 vindices2[3], CVector3 vindices3[3], CVector3 vindicest[4]);
};