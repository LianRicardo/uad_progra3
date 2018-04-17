#pragma once

#include "CApp.h"
#include "..\Include\CCamera.h"
#include "CWorld.h"
#include "COpenGLRenderer.h"
#include "CGameGrid.h"
#include "CHex.h"
#include "Globals.h"
#include "CApp.h"
#include "C3DModel.h"
#include "CVector3.h"
#include "CLoger.h"

class CappProyecto : public CApp
{
private:
	CWorld *myWorld;
public:
	CappProyecto();
	CappProyecto(int window_width, int window_height);
	
	~CappProyecto();
	CGameGrid * pgrid;
	bool inicialize();
	void inicialized();
	void update(double delta_time);
	void run();
	void render();   //esta funcion tiene que mandar a llamar a la funcion de world render que adentro debe hacer el render del grid y mandar a llamar a renderwireframeobj
	bool initializeMenu();
	double m_currentDeltaTime;
	void onMouse(float deltaX, float deltaY);

};