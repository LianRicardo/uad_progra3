#pragma once

#include "..\Include\CVector3.h"


class CCamera
{
private:
	CVector3 initialPos;
	CVector3 position;
	CVector3 lookAt;
	CVector3 upVec;
public:
	CCamera();
	~CCamera();
	void move(float deltaX, float deltaY);
	void reset();
	CVector3 getPosition();
};
