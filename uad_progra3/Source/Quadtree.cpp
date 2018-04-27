#include "..\Include\Quadtree.h"

Quadtree::Quadtree(CGameGrid *pgrid) :
	pgrid(pgrid)
{

}

Quadtree::~Quadtree()
{

}

bool Quadtree::Inicializarq()
{
	// Points that I need to build the QuadTree
	CVector3 cuartopunto;
	CVector3 tercerpunto;
	CVector3 ultimopunto;
	CVector3 primerpunto;

	cuartopunto = pgrid->getcell(0, 0, 4);
	tercerpunto = pgrid->getcell(0, 0, 3);
	ultimopunto = pgrid->getcell(GRID_SIZE - 1, 0, 1);
	primerpunto = pgrid->getcell(GRID_SIZE - 1, GRID_SIZE - 1, 0);

	VertexR[0].setValues(cuartopunto.getX(), 0, tercerpunto.getZ());
	VertexR[1].setValues(ultimopunto.getX(), 0, primerpunto.getZ());
	for (size_t i = 0; i < 2; i++)
	{
		cout << VertexR[i].getX() << "   ";
		cout << VertexR[i].getZ();
		cout << std::endl;
	}
	//return false;
	return true;
}

CVector3* Quadtree::getVertexR()
{
	return VertexR;
}

