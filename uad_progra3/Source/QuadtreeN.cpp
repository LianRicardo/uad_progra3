#include "..\Include\QuadtreeN.h"


QuadtreeN::QuadtreeN(CVector3* vertexn, CGameGrid* pgrid) :
	tl(nullptr),
	tr(nullptr),
	dl(nullptr),
	dr(nullptr)
{
	Log << "Constructor quadtreenode" << endl;
	center.setValues((vertexn[0].getX() + vertexn[1].getX()) / 2, 0, (vertexn[0].getZ() + vertexn[1].getZ()) / 2);
}

QuadtreeN::~QuadtreeN()
{
	Log << "destructor quadtreenode" << endl;
}

void QuadtreeN::dividir(CGameGrid* pgrid)
{
	for (size_t i = 0; i < GRID_SIZE; i++)
	{
		for (size_t j = 0; j < GRID_SIZE; j++)
		{

		}
	}
	return;
}