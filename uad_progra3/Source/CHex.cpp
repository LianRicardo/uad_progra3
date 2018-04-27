#include "..\Include\CHex.h"

CHex::CHex(float x, float y, const float s, float a) : graphicMemoryObjectId(nullptr)
{
	    center.setValues(x, 0, y);
		v[0].setValues(center.getX() + (s / 2.0f), 0, center.getZ() - a);
		v[1].setValues(center.getX() + s, 0, center.getZ());
		v[2].setValues(center.getX() + (s / 2.0f), 0, center.getZ() + a);
		v[3].setValues(center.getX() - (s / 2.0f), 0, center.getZ() + a);
		v[4].setValues(center.getX() - s, 0, center.getZ());
		v[5].setValues(center.getX() - (s / 2.0f), 0, center.getZ() - a);
}
CHex::~CHex()
{
	Log << "destructor de la celda";
	center = { 0,0,0 };
	pos = { 0,0,0 };
	v[0] = { 0,0,0 };
	v[1] = { 0,0,0 };
	v[2] = { 0,0,0 };
	v[3] = { 0,0,0 };
	v[4] = { 0,0,0 };
	v[5] = { 0,0,0 };
}

void CHex::getVertices(float * vertex)
{
	vertex[0] = v[0].getX();
	vertex[1] = v[0].getY();
	vertex[2] = v[0].getZ();
	vertex[3] = v[1].getX();
	vertex[4] = v[1].getY();
	vertex[5] = v[1].getZ();
	vertex[6] = v[2].getX();
	vertex[7] = v[2].getY();
	vertex[8] = v[2].getZ();
	vertex[9] = v[3].getX();
	vertex[10] = v[3].getY();
	vertex[11] = v[3].getZ();
	vertex[12] = v[4].getX();
	vertex[13] = v[4].getY();
	vertex[14] = v[4].getZ();
	vertex[15] = v[5].getX();
	vertex[16] = v[5].getY();
	vertex[17] = v[5].getZ();
}
