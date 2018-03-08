#pragma once
#include <iostream>

#define cout CLoger::getloger()->out()

class CLoger
{
protected:
	CLoger();
private:
	static CLoger* single;
protected:
	std::ostream * stream;
public:
	virtual ~CLoger();
	static CLoger* getloger();
	std::ostream& const out(){ return *stream; }
};