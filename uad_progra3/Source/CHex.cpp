#include "..\Include\CHex.h"

CHex::CHex()
{
	Log << "constructor de la matrix. \n";
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