#pragma once
#include "CLoger.h"
#include<fstream>
#include<string>
class CArchivo : public CLoger
{
protected:
	CArchivo();
private:
	static CArchivo* single;
	std::fstream archivo;
	std::string filename();
public:
	~CArchivo();
	static CArchivo* getfileloger();
};