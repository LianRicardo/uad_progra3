#include "..\Include\CWorld.h"
#include "..\Include\Globals.h"
#include <CWideStringHelper.h>

CWorld::CWorld(COpenGLRenderer *r) : r(r)
{
	gamegrid = new CGameGrid();
	inicializado = false;
}

CWorld::~CWorld()
{
	//gamegrid = NULL;
	delete gamegrid;
}

void CWorld::render()
{
	if (inicializado)
	{
		float color[3] = { 0.95f, 0.95f, 0.95f };
		double totalDegreesRotatedRadians = 0 * 3.1459 / 180.0;
		CVector3 zero = { 0,0,0 };
		MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, zero);
		//size_t ID = 0;
		r->renderWireframeObject(&(gamegrid->shaderid),&(gamegrid->vaoID), getn_vertexindex(), color, &modelMatrix);
	}
	else Log << "error en la matriz" << endl;
}

bool CWorld::init()
{
	gamegrid->inicializar();
	//COpenGLRenderer* r = getOpenGLRenderer();
	unsigned int sid = gamegrid->shaderid;
	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::wstring wresourceFilenameTexture;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;
	std::string resourceFilenameTexture;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_MENU, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_MENU, wresourceFilenameFS, resourceFilenameFS) ||
		!CWideStringHelper::GetResourceFullPath(MENU_TEXTURE_FILE, wresourceFilenameTexture, resourceFilenameTexture))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << VERTEX_SHADER_MENU << endl;
		cout << "  " << FRAGMENT_SHADER_MENU << endl;
		cout << "  " << MENU_TEXTURE_FILE << endl;
		return false;
	}
	r->createShaderProgram(&sid, resourceFilenameVS.c_str(), resourceFilenameFS.c_str());

	if (gamegrid->grid == NULL)
	{
		cout << "error en el mundo wtfffff" << endl;
		inicializado = false;
		return inicializado;
	}
	else
	{
		r->allocateGraphicsMemoryForObject(&(gamegrid->shaderid), &(gamegrid->vaoID),getvertex(),getn_vertex(),getvertexindex(),getn_vertexindex());
		inicializado = true;
		return inicializado;
	}
}

float* CWorld::getvertex()
{
	return gamegrid->vindexpos.data();
}
size_t CWorld::getn_vertex()
{
	return gamegrid->vindexpos.size();
}
unsigned short* CWorld::getvertexindex()
{
	return gamegrid->vindex.data();
}
size_t CWorld::getn_vertexindex()
{
	return gamegrid->vindex.size();
}


void save()
{

}

void load()
{

}
