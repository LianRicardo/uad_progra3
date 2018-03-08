#include "..\Include\CHex.h"


CHex::CHex(float x, float y)
{
	Log << "constructor de la celda. \n";
	v[0].setValues(x + (size / 2), 0, y - radius);
	v[1].setValues(x + size, 0, y);
	v[2].setValues(x + (size / 2), 0, y + radius);
	v[3].setValues(x - (size / 2), 0, y + radius);
	v[4].setValues(x - size, 0, y);
	v[5].setValues(x - (size / 2), 0, y - radius);

	pos.setValues(x, 0, y );

	/*centerx = v[5] + ((v[5] + v[1]) / 2);
	centery= v[4] + ((v[4] + v[2]) / 2);
	
	center.setValues(centerx.getX(), 0, centery.getZ());*/
}
CHex::CHex()
{

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

void CHex::set(CVector3 center, CVector3 pos, CVector3 v[6])
{
	CHex objeto;
	center = objeto.center;
	pos = objeto.pos;
	v[0] = objeto.v[0];
	v[1] = objeto.v[1];
	v[2] = objeto.v[2];
	v[3] = objeto.v[3];
	v[4] = objeto.v[4];
	v[5] = objeto.v[5];
}