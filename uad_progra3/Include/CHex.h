#pragma once


#include "CVector3.h"
#include "CLoger.h"
#include <iostream>

class CHex
{
	CVector3 v[6];
	CVector3 center;
	CVector3 pos;
	const float size = 1.0f;
	const float radius = 0.866025f;
	float altura;
	float ancho;
	void set(CVector3 center, CVector3 pos, CVector3 v[6]);
public:
	CVector3 getcenter(CVector3 centerx, CVector3 centery, CVector3 center)
	{
		centerx = v[5] + ((v[5] + v[1]) / 2);
		centery = v[4] + ((v[4] + v[2]) / 2);

		center.setValues(centerx.getX(), 0, centery.getZ());
	}
	void getvertex(CVector3 v[6], int x, int y)
	{
		v[0].setValues(x + (size / 2), 0, y - radius);
	    v[1].setValues(x + size, 0, y);
	    v[2].setValues(x + (size / 2), 0, y + radius);
	    v[3].setValues(x - (size / 2), 0, y + radius);
	    v[4].setValues(x - size, 0, y);
	    v[5].setValues(x - (size / 2), 0, y - radius);
	}
	CHex::CHex();
	CHex(float x, float y);
	~CHex();
};