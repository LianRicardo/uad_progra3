#include "..\Include\CGameGrid.h"
#include "..\Include\COpenGLRenderer.h"
#include "..\Include\CLoger.h"


CGameGrid::CGameGrid()
{
	vaoID = 0;
}

CGameGrid::~CGameGrid()
{
	Log << "destructor de grid" << endl;
	CloseHandle(thread1);
}


DWORD WINAPI CGameGrid::inicializar(PVOID pv_param)
{
	CGameGrid* instancia = (CGameGrid*)pv_param;
	//Sleep(1500);
	cout << "soy el primer thread " << endl;
	cout << "inicializando grid" << endl;
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			//grid[i][j] = new CHex()
			instancia->grid[i][j].inicializarhexcell(i, j);
			//inicializar vertices
			for (int k = 0; k < 6; k++)
			{
				instancia->vindexpos.push_back(instancia->grid[i][j].v[k].getX());
				instancia->vindexpos.push_back(instancia->grid[i][j].v[k].getY());
				instancia->vindexpos.push_back(instancia->grid[i][j].v[k].getZ());
			}

			//CALCULAR INDICES

			for (int l = 0; l < 4; l++)
			{
				instancia->vindex.push_back(i * GRID_SIZE * 6 + j * 6);
				instancia->vindex.push_back(i * GRID_SIZE * 6 + j * 6 + l + 1);
				instancia->vindex.push_back(i * GRID_SIZE * 6 + j * 6 + l + 2);
			}
		}
	}
	cout << "grid inicializada" << endl;
	return true;
}

/*bool CGameGrid::inicializar()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			//grid[i][j] = new CHex();
			grid[i][j].inicializarhexcell(i, j);
			//inicializar vertices
			for (int k = 0; k < 6; k++)
			{
				vindexpos.push_back(grid[i][j].v[k].getX());
				vindexpos.push_back(grid[i][j].v[k].getY());
				vindexpos.push_back(grid[i][j].v[k].getZ());
			}

			//CALCULAR INDICES 

			for (int l = 0; l < 4; l++)
			{
				vindex.push_back(i * GRID_SIZE * 6 + j * 6);
				vindex.push_back(i * GRID_SIZE * 6 + j * 6 + l + 1);
				vindex.push_back(i * GRID_SIZE * 6 + j * 6 + l + 2);
			}

			//n_trigs += 4;
			//n_vertex += 6;
		}
	}
	return true;
}*/


int CGameGrid::returnn()
{
	return GRID_SIZE*GRID_SIZE*4;
}

