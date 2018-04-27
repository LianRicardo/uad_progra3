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


#define CAMERA_SPEED 1.0
class CappProyecto : public CApp
{
private:
	CGameGrid* gamegrid;
	CWorld *myWorld;
	double m_currentDeltaTime;
	double m_objectRotation;
	CVector3 m_objectPosition;
	double m_rotationSpeed;
public:
	CappProyecto();
	CappProyecto(int window_width, int window_height);
	~CappProyecto();
	bool inicialize();
	void inicialized();
	void update(double delta_time);
	void run();
	void render();   //esta funcion tiene que mandar a llamar a la funcion de world render que adentro debe hacer el render del grid y mandar a llamar a renderwireframeobj
	bool initializeMenu();
	void onMouse(float deltaX, float deltaY);
	void onF3(int mods);
	void moveCamera(float direction);
};