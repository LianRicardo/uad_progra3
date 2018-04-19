#pragma once

#include "CHex.h"
#include "CVector3.h"
#include <vector>
using namespace std;


class CGameGrid
{
public:
	//unsigned int shaderid;
	CGameGrid();
	//COpenGLRenderer * const r;
	unsigned int vaoID;
	CHex grid[100][100];
	std::vector<unsigned short> vindex;
	std::vector<float> vindexpos;
	int n_trigs = 0;
	//int n_vertex = 0;
	bool inicializar();
	int returnn();
};