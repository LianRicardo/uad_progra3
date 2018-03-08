#include "..\Include\CCamera.h"

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

void CCamera::move(float deltaX, float deltaY)
{
	if (deltaX < 100.0f && deltaY < 100.0f)
	{
		float val[3];
		pos.getValues(val);
		val[0] += deltaX;
		val[2] += deltaY;
		pos.setValues(val);
	}
}

void CCamera::reset()
{

}
