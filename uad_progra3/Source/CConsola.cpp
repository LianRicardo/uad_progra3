#include "..\Include\CConsola.h"

CConsola* CConsola::single = 0;

CConsola::CConsola()
{
	stream = &std::cout;
}

CConsola::~CConsola()
{

}

CConsola * CConsola::getconsoleloger()
{
	if (single == 0) {
		single = new CConsola();
	}
	return single;
}