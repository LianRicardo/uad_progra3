#include "..\Include\CArchivo.h"
#include <ctime>
#include <Windows.h>

CArchivo* CArchivo::single = 0;
CArchivo::CArchivo()
{
	std::string nombre = filename();
	stream = &archivo;
	std::string stack;

	if (getenv("PROGRA3_TEMP"))
	{
		stack = getenv("PROGRA3_TEMP");
	}
	else if (getenv("TEMP"))
	{
		stack = getenv("TEMP");
	}
	else throw new std::runtime_error("No tienes variables temporales todavia");
	stack += "\\";
	stack += nombre;
	archivo.open(stack, std::ios::out);
	archivo << nombre;
}

CArchivo::~CArchivo()
{
	archivo.close();
}



std::string CArchivo::filename()
{
	char str[20];
	time_t rawtime;
	struct tm timedata;
	time(&rawtime);
	localtime_s(&timedata, &rawtime);
	strftime(str, 100, "%d_%m_%y_%H-%M-%S", &timedata);

	char filename[MAX_PATH];
	DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH);
	if (!size)
		std::cout << "Could not find EXE file name.\n";

	char *nextToken = NULL;
	char *token = NULL;
	char *tokenSaver = NULL;

	const char *delimiter = "\\";
	const char *delimiter2 = ".";

	token = strtok_s(filename, delimiter, &nextToken);
	while (token) {
		tokenSaver = token;
		token = strtok_s(NULL, delimiter, &nextToken);
	}
	token = strtok_s(tokenSaver, delimiter2, &nextToken);

	std::string str1(token);
	str1 += "_";
	str1 += str;
	str1 += ".log";

	return str1;
}

CArchivo* CArchivo::getfileloger()
{
	if (single == 0) {
		single = new CArchivo();
	}
	return single;
}