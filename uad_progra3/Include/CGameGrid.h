#pragma once

#include "CHex.h"
#include "CVector3.h"
#include <vector>
#include <Windows.h>
#include <iostream>
using namespace std;

#define GRID_SIZE 3
class CGameGrid
{
public:
	//unsigned int shaderid;
	CGameGrid();
	~CGameGrid();
	//COpenGLRenderer * const r;
	unsigned int vaoID;
	CHex grid[GRID_SIZE][GRID_SIZE];
	std::vector<unsigned short> vindex;
	std::vector<float> vindexpos;
	int n_trigs = 0;
	DWORD hextrhead_id;
	//int n_vertex = 0;
	static DWORD WINAPI inicializar(PVOID pv_param);
	//bool inicializar();
	HANDLE thread1;
	int returnn();
};