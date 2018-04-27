#pragma once


#include "CVector3.h"
#include "CLoger.h"
#include <iostream>
#include <math.h>

class CHex
{
public:
	CVector3 center;
	CVector3 pos;
	CVector3 v[6];
	unsigned int *graphicMemoryObjectId;
	//const float s = sqrt(3) / 2;
	unsigned int texture_id;
	const float s = 1.0f;
	void getVertices(float * v);
	CVector3 CHex::getpoint(int p)
	{
		return v[p];
	}
	void CHex::settexture_id(unsigned int texture_id)
	{
		this->texture_id = texture_id;
	}
	CVector3 CHex::getcenter()
	{
		return this->center;
	}
	unsigned int * CHex::getGraphicMemoryObjectId()
	{
		return graphicMemoryObjectId;
	}
	CHex(float x, float y, const float s, float a);
	~CHex();
};