#include "..\Include\CWorld.h"

CWorld::CWorld()
{

}

CWorld::~CWorld()
{
	//gamegrid = NULL;
	delete &(gamegrid);
}

void CWorld::render()
{
	if (gamegrid.inicializar())
	{
		float color[3] = { 0.95f, 0.95f, 0.95f };
		double totalDegreesRotatedRadians = 0 * 3.1459 / 180.0;
		CVector3 zero = { 0,0,0 };
		MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, zero);
		size_t ID = 0;
		r->renderWireframeObject(&(gamegrid.shaderid),&(gamegrid.shaderid1), getn_vertexindex(), color, &modelMatrix);
	}
	else Log << "error en la matriz" << endl;
}

bool CWorld::init()
{
	gamegrid.inicializar();
	if (gamegrid.grid == NULL)
	{
		return false;
	}
	else
	{
		r->allocateGraphicsMemoryForObject(&(gamegrid.shaderid), &(gamegrid.shaderid1),getvertex(),getn_vertex(),getvertexindex(),getn_vertexindex());
		return true;
	}
}

float* CWorld::getvertex()
{
	return gamegrid.vindexpos.data();
}
size_t CWorld::getn_vertex()
{
	return gamegrid.vindexpos.size();
}
unsigned short* CWorld::getvertexindex()
{
	return gamegrid.vindex.data();
}
size_t CWorld::getn_vertexindex()
{
	return gamegrid.vindex.size();
}


void save()
{

}

void load()
{

}
