#include "..\Include\CWorld.h"
#include "..\Include\Globals.h"
#include <CWideStringHelper.h>
#include <LoadTGA.h>

CWorld::CWorld(COpenGLRenderer *r) : r(r)
{
	qt = nullptr;
	gamegrid = new CGameGrid(r);
	inicializado = false;
	m_TextureNames.resize(4);
	m_TextureNames = { TEXTURE_GRID };
	m_TexturesID = { 0,0,0,0 };
}

CWorld::~CWorld()
{
	r->freeGraphicsMemoryForObject(&sid, &gamegrid->vaoID);
	delete gamegrid;
}

void CWorld::render(CVector3 cpos)
{
	float color[3] = { 0.95f, 0.95f, 0.95f };
	for (size_t i = 0; i < GRID_SIZE; i++)
	{
		for (size_t j = 0; j < GRID_SIZE; j++)
		{

			float x, y, z;
			x = gamegrid->getCenter(i, j).getX() + cpos.getX();
			y = gamegrid->getCenter(i, j).getY() + cpos.getY();
			z = gamegrid->getCenter(i, j).getZ() + cpos.getZ();
			MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CVector3(x, y, z));

			r->renderMCCube(&modelMatrix);
		}
	}
}

bool CWorld::init()
{
	gamegrid = new CGameGrid(r);
	gamegrid->inicializar();
	for (int i = 0; i < 4; i++)
	{
		std::wstring wresourceFiletexture;
		std::string resourceFileTexture;
		// If resource files cannot be found, return
		if (!CWideStringHelper::GetResourceFullPath(m_TextureNames[i].c_str(), wresourceFiletexture, resourceFileTexture))
		{
			Log << "ERROR: Unable to find one or more resource textures: " << endl;
		}
		TGAFILE tgaFile;
		tgaFile.imageData = NULL;
		unsigned int mc = -1;
		if (LoadTGAFile(resourceFileTexture.c_str(), &tgaFile))
		{
			if (tgaFile.imageData == NULL ||
				tgaFile.imageHeight < 0 ||
				tgaFile.imageWidth < 0)
			{
				if (tgaFile.imageData != NULL)
				{
					delete[] tgaFile.imageData;
				}
				return false;
			}

			// Create a texture object for the menu, and copy the texture data to graphics memory
			if (!r->createTextureObject(
				&m_TexturesID[i],
				tgaFile.imageData,
				tgaFile.imageWidth,
				tgaFile.imageHeight
			))
			{
				return false;
			}

			// Texture data is stored in graphics memory now, we don't need this copy anymore
			if (tgaFile.imageData != NULL)
			{
				delete[] tgaFile.imageData;
			}
		}
		else
		{
			// Free texture data
			if (tgaFile.imageData != NULL)
			{
				delete[] tgaFile.imageData;
			}

			return false;
		}
		inicializado = true;
		r->initializeMCCube(mc);
	}

	//myHexGrid->createTextureWorld(&m_TexturesID);

	return true;
}

float* CWorld::getvertex()
{
	return gamegrid->vindexpos.data();
}
size_t CWorld::getn_vertex()
{
	return gamegrid->vindexpos.size()/3;
}
unsigned short* CWorld::getvertexindex()
{
	return gamegrid->vindex.data();
}
size_t CWorld::getn_vertexindex()
{
	return gamegrid->vindex.size()/3;
}

bool CWorld::inicializarqt()
{
	qt = new Quadtree(gamegrid);
	qt->Inicializarq();
	cout << "quad tree inicializado " << endl;
	return true;
}

void save()
{

}

void load()
{

}
