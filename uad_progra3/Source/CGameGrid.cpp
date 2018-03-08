#include "..\Include\CGameGrid.h"
#include "..\Include\COpenGLRenderer.h"

bool CGameGrid::inicializar(CVector3 v[6], CVector3 pos, CVector3 center, CVector3 centerx, CVector3 centery, CVector3 vindices[3],CVector3 vindices1[3],CVector3 vindices2[3],CVector3 vindices3[3], CVector3 vindicest[4])
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			grid[100][100].getvertex(v[6], i, j);
			grid[100][100].getcenter(centerx, centery, center);
			vindices[3].setValues = { v[0],v[4],v[5] };
			vindices1[3].setValues = { v[0], v[1],v[4] };
			vindices2[3].setValues = { v[1],v[3],v[4] };
			vindices3[3].setValues = { v[1],v[2],v[3] };
			vindicest[4].setValues = { vindices[3],vindices1[3],vindices2[3],vindices3[3] };
			/*allocateGraphicsMemoryForObject(
				const unsigned int * const shaderProgramId,
				unsigned int *vertexArrayObjectID,
				GLfloat *vertices, int numVertices,
				unsigned short *indicesVertices, int numIndicesVert)*/
		}
	}
}