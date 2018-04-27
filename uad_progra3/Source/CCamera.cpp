#include "..\Include\CCamera.h"



CCamera::CCamera() :
	position(0, 0, 0)
{
}


CCamera::~CCamera()
{
}

void CCamera::move(float deltaX, float deltaY)
{
	position.setValues(position.getX() + deltaX, position.getY(), position.getZ() + deltaY);
}

void CCamera::reset()
{

}

CVector3 CCamera::getPosition()
{
	return position;
}
