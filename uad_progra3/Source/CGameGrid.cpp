#include "..\Include\CGameGrid.h"
#include "..\Include\COpenGLRenderer.h"

void CGameGrid::inicializar()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			grid[i][j].inicializarhexcell(i, j);

			//inicializar vertices
			for (int k = 0; k < 6; k++)
			{
				trigraw.push_back(grid[i][j].v[k].getX());
				trigraw.push_back(grid[i][j].v[k].getY());
				trigraw.push_back(grid[i][j].v[k].getZ());
			}

			//CALCULAR INDICES 

			for (int l = 0; l < 4; l++)
			{
				trig_id.push_back(i * 100 * 6 * 3 + j * 6 * 3);
				trig_id.push_back(i * 100 * 6 * 3 + j * 6 * 3 + l + 1);
				trig_id.push_back(i * 100 * 6 * 3 + j * 6 * 3 + l + 2);
			}

			n_trigs += 4;
			n_vertex += 6;
		}
	}
}

/*allocateGraphicsMemoryForObject(
const unsigned int * const shaderProgramId,
unsigned int *vertexArrayObjectID,
GLfloat *vertices, int numVertices,
unsigned short *indicesVertices, int numIndicesVert)*/