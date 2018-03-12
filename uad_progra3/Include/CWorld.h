#pragma once

#include "CGameGrid.h"

class CWorld
{
public:
	void save();
	void load();
	CWorld();
	~CWorld();
	CGameGrid gamegrid;
	
};