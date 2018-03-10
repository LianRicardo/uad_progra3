#pragma once

#include "CHex.h"
#include "CVector3.h"
#include <vector>
using namespace std;


class CGameGrid
{
	CHex grid[100][100];
	std::vector<size_t> trig_id;
	std::vector<float> trigraw;
	int n_trigs = 0;
	int n_vertex = 0;
	void inicializar();
};