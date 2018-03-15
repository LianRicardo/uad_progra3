#include "..\Include\CGameGrid.h"
#include "..\Include\COpenGLRenderer.h"

bool CGameGrid::inicializar()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
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
				vindex.push_back(i * 100 * 6 * 3 + j * 6 * 3);
				vindex.push_back(i * 100 * 6 * 3 + j * 6 * 3 + l + 1);
				vindex.push_back(i * 100 * 6 * 3 + j * 6 * 3 + l + 2);
			}

			//n_trigs += 4;
			//n_vertex += 6;
		}
		return true;
	}
}


