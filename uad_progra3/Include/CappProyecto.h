#pragma once

#include "CApp.h"
#include "..\Include\CCamera.h"
#include "CWorld.h"

class CappProyecto : public CApp
{
private:
	CWorld myWorld;

public:
	CappProyecto();
	~CappProyecto();

	virtual void onMouse(float deltaX, float deltaY);
};