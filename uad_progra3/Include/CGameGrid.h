#pragma once

#include "CHex.h"
#include "CVector3.h"
#include <vector>
#include <Windows.h>
#include <iostream>
#include "Globals.h"
#include <COpenGLRenderer.h>
using namespace std;

#define GRID_SIZE 3
class CGameGrid
{
public:
	CGameGrid(COpenGLRenderer * r);
	~CGameGrid();
	const float s = 0.5f;
	COpenGLRenderer * const r;
	const float a = sqrt(3)*(s / 2);
	unsigned int vaoID;
	CHex * grid[GRID_SIZE][GRID_SIZE];
	std::vector<unsigned short> vindex;
	std::vector<float> vindexpos;
	//DWORD hextrhead_id;
	//static DWORD WINAPI inicializar(PVOID pv_param);
	bool inicializar();
	int returnn();
	CVector3 CGameGrid::getCenter(int i, int j)
	{
		return grid[i][j]->getcenter();
	}
	unsigned int gridShaderProgramID;
	unsigned int * getVAOIDTexture();
	unsigned int gridVAOIDTexture;
	CVector3 getcell(int x, int y, int p);
	void texturegamegrid(vector<unsigned int>* textureID);
};