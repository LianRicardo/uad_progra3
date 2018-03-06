#include "..\Include\CLoger.h"
#include <iostream>
#include "..\Include\CArchivo.h"
#include "..\Include\CConsola.h"

CLoger* CLoger::single = 0;

CLoger::CLoger()
{

}
CLoger::~CLoger()
{

}


CLoger * CLoger::getloger()
{
	if (getenv("console_files"))
	{
		single = CArchivo::getfileloger();
	}

	else 
	{
		single = CConsola::getconsoleloger(); ;
	}
	return single;
}