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
	CWorld myWorld;

public:
	CappProyecto();
	~CappProyecto();
	CGameGrid * p;
	bool inicialize();
	COpenGLRenderer * r;
	virtual void update(double delta_time);
	virtual void run();
	virtual void render();
	virtual bool initializeMenu();
	size_t id = 0;
	// Pointer to an object of type C3DModel
	C3DModel *m_p3DModel;

	// Current delta time (time of the current frame - time of the last frame)
	double m_currentDeltaTime;

	// Current object rotation, expressed in degrees
	double m_objectRotation;

	// Current object position
	CVector3 m_objectPosition;

	//  Object rotation speed (degrees per second)
	double m_rotationSpeed;
	
	virtual void onMouse(float deltaX, float deltaY);

public:
	float* getvertex();
	size_t getn_vertex();
	unsigned short* getvertexindex();
	size_t getn_vertexindex();

};