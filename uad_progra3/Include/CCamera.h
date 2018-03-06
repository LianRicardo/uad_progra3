#pragma once

#include "..\Include\CVector3.h"

class CCamera
{
private:
	CVector3 initialPos;
	CVector3 pos;
	CVector3 lookAt;
	CVector3 upVec;
public:
	CCamera();
	~CCamera();
	void reset();
	void move(float deltaX, float deltaY);
};