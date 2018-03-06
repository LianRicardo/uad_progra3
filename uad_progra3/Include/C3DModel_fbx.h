#pragma once

#include <string>
using namespace std;
#include "C3DModel.h"
#include "CVector3.h"



/*class C3DModel_fbx : public C3DModel
{
public:
	//~C3DModel_fbx();
	//C3DModel_fbx();

private:
	CVector3 *m_vertices;          // Dynamically-allocated array of vertices
	CVector3 *m_normals;           // Dynamically-allocated array of normals
	CVector3 *m_UVCoords;          // Dynamically-allocated array of UV coords
public:
	void reset();
	// Methods to read a model in the .obj file format
protected:
	bool loadFromFile(const char * const filename)
	{
		//FbxUtil::Stream fs;
		//FbxScene scn;
		/*const char** argv;
		auto srcfile = argv[1];
		if (!srcfile) {
			srcfile = "cube.fbx";
		}
		fs.open(srcfile, ios_base::in);
		if (!fs) {
			printf("could not open %s", srcfile);
			return 0;
		}
		//LoadFbx(&scn, fs);       //tengo que hallar una forma de pasarle el const char* const para que el header lo agarre y lo lea
	}
};*/