#pragma once

#ifndef C3DMODEL_obj_H
#define C3DMODEL_obj_H

#include <string>
using namespace std;
#include "C3DModel.h"
#include "CVector3.h"

class C3DModel_obj: public C3DModel
{
public:
	~C3DModel_obj();
	C3DModel_obj();

private:
	CVector3 *m_vertices;          // Dynamically-allocated array of vertices
	CVector3 *m_normals;           // Dynamically-allocated array of normals
	CVector3 *m_UVCoords;          // Dynamically-allocated array of UV coords
public:
	void reset();
								   // Methods to read a model in the .obj file format
	bool readFile(const char * const filename, bool countOnly);       // Read object from file 
	bool parseLine(std::string line, bool countOnly, int lineNumber); // Parse line
protected:
	bool loadFromFile(const char * const filename);
};

#endif