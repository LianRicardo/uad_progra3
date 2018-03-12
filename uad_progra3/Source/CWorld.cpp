#include "..\Include\CWorld.h"

CWorld::CWorld()
{
	gamegrid.inicializar();
}

CWorld::~CWorld()
{
	//gamegrid = NULL;
	delete &(gamegrid);
}

void save()
{

}

void load()
{

}
