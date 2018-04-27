#include "..\Include\CGameGrid.h"
#include "..\Include\COpenGLRenderer.h"
#include "..\Include\CLoger.h"
#include <CWideStringHelper.h>


CGameGrid::CGameGrid(COpenGLRenderer * r) : r(r)
{
	vaoID = 0;
}

CGameGrid::~CGameGrid()
{
	Log << "destructor de grid" << endl;
	//CloseHandle(thread1);
}


/*DWORD WINAPI CGameGrid::inicializar(PVOID pv_param)
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
}*/

bool CGameGrid::inicializar()
{
	/*float x = 0;
	float y = 0;
	if (GRID_SIZE % 2 == 0) 
	{
		x = -1 * ((1.0f * 2 * (GRID_SIZE / 2)) + ((GRID_SIZE / 2)*1.0f)) / 2;
		y = x;
	}
	else 
	{
		x = -1 * ((((GRID_SIZE / 2) + 1) * 2 * 1.0f) + ((GRID_SIZE / 2)*1.0f)) / 2;
		y = x;
	}
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			grid[i][j] = new CHex(i, j, x, y);
			//inicializar vertices
			for (int k = 0; k < 6; k++)
			{
				vindexpos.push_back(grid[i][j]->v[k].getX());
				vindexpos.push_back(grid[i][j]->v[k].getY());
				vindexpos.push_back(grid[i][j]->v[k].getZ());
			}

			//CALCULAR INDICES 

			for (int l = 0; l < 4; l++)
			{
				vindex.push_back(i * GRID_SIZE * 6  + j * 6);
				vindex.push_back(i * GRID_SIZE * 6  + j * 6 + l + 1);
				vindex.push_back(i * GRID_SIZE * 6  + j * 6 + l + 2);
			}
		}
	}
	return true;*/
	// Temp array that saves XYZ of just one hexcell
	float v[6 * 3];

	// Array that saves XYZ of each hexcell
	float *verticesRaw = new float[sizeof(float)*(GRID_SIZE *GRID_SIZE * 6 * 3)];

	// Indices that indicates the order of triangles inner the hex
	unsigned short *indices = new unsigned short[3 * 4 * GRID_SIZE * GRID_SIZE];

	// Pos of first hexagon, calculates size of center
	float x = 0, y = 0;

	// HexLayout, if center is even then it adds 1/2 to X(i) else (odd) it adds 1/2 to X(i) and 1 to Y(j)
	// Then it creates the VerticesRaw array. It has XYZ of each vertex
	size_t offset = 0;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {

			// First hexagon
			if (i == 0)
				if (j == 0)
					grid[i][j] = new CHex(x, y, s, a);

			// http://webdevtipstricksandinfo.blogspot.mx/2012/08/creating-hexagonal-grid-for-games-c-java.html
			grid[i][j] = new CHex(x + j * ((3 * s) / 2), y + (j % 2)*a + 2 * i*a, s, a);

			grid[i][j]->getVertices(v);
			memcpy(&verticesRaw[offset], v, sizeof(float) * (6 * 3));
			offset += 6 * 3;
		}
	}

	unsigned short singleHexIndices[] = {
		2,1,0,
		3,5,4,
		3,0,5,
		2,0,3 };

	size_t inOffset = 0;
	size_t outOffset = 0;
	for (size_t i = 0; i < GRID_SIZE; i++) {
		for (size_t j = 0; j < GRID_SIZE; j++) {
			for (size_t k = 0; k < 12; k++) {
				indices[inOffset + k] = singleHexIndices[k] + outOffset;
			}
			outOffset += 6;
			inOffset += 12;
		}
	}

	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_WIREFRAME, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_WIREFRAME, wresourceFilenameFS, resourceFilenameFS))
	{
		Log << "ERROR: Unable to find one or more resources: " << endl;
		Log << "  " << VERTEX_SHADER_WIREFRAME << endl;
		Log << "  " << FRAGMENT_SHADER_WIREFRAME << endl;
		return false;
	}
	r->createShaderProgram(
		&gridShaderProgramID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str());
	r->allocateGraphicsMemoryForObject(
		&gridShaderProgramID,
		&vaoID, verticesRaw,
		GRID_SIZE * GRID_SIZE * 6,
		indices, returnn());
	delete[] verticesRaw;
	delete[] indices;
	return true;
}

unsigned int * CGameGrid::getVAOIDTexture()
{
	return &gridVAOIDTexture;
}
int CGameGrid::returnn()
{
	return GRID_SIZE*GRID_SIZE*4;
}

CVector3 CGameGrid::getcell(int x, int y, int p)
{
	return grid[x][y]->getpoint(p);
}

void CGameGrid::texturegamegrid(vector<unsigned int>* textureID)
{
	for (size_t i = 0; i < 100; i++) {
		for (size_t j = 0; j < 100; j++) {
			if (i > GRID_SIZE / 2 && j > GRID_SIZE / 2)
				grid[i][j]->settexture_id(textureID->at(0));
			if (i > GRID_SIZE / 2 && j < GRID_SIZE / 2)
				grid[i][j]->settexture_id(textureID->at(1));
			if (i < GRID_SIZE / 2 && j > GRID_SIZE / 2)
				grid[i][j]->settexture_id(textureID->at(2));
			if (i < GRID_SIZE / 2 && j < GRID_SIZE / 2)
				grid[i][j]->settexture_id(textureID->at(3));
		}

	}
}


