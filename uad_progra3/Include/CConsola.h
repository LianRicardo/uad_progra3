#pragma once
#include "CLoger.h"


class CConsola : public CLoger
{
private:
	static CConsola* single;
protected:
	CConsola();
public:
	~CConsola();
	static CConsola* getconsoleloger();
};