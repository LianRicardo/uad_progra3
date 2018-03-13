#pragma once


#include "CVector3.h"
#include "CLoger.h"
#include <iostream>
#include <math.h>

class CHex
{
	void set(CVector3 center, CVector3 pos, CVector3 v[6]);
public:
	CVector3 center;
	CVector3 pos;
	CVector3 v[6];
	const float size = sqrt(3) / 2;
	void inicializarhexcell(int id_x, int id_y)
	{
		v[0].setValues(id_x - size, 0, id_y);
		v[1].setValues(id_x - (size / 2), 0, id_y + 0.5);
		v[2].setValues(id_x + (size / 2), 0, id_y + 0.5);
		v[3].setValues(id_x + size, 0, id_y);
		v[4].setValues(id_x + (size/2), 0, id_y - 0.5);
		v[5].setValues(id_x - (size / 2), 0, id_y - 0.5);
		center.setValues(id_x*(sqrt(3) / 2), 0, id_y - (id_y % 2 != 0) ? 0.5 : 0);
	}
	CHex();
	~CHex();
};