#pragma once

#include "CHex.h"
#include "CVector3.h"
#include <vector>
using namespace std;


class CGameGrid
{
public:
	unsigned int shaderid;
	unsigned int shaderid1;
	CHex grid[100][100];
	std::vector<unsigned short> vindex;
	std::vector<float> vindexpos;
	//int n_index = 0;
	//int n_vertex = 0;
	bool inicializar();

};