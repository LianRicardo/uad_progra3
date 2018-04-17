#include"..\\Include\CappProyecto.h"
#include "windows.h"
#include "../Include/Globals.h"
#include "../Include/CAppParcial2.h"
#include "../Include/C3DModel.h"
#include "../Include/LoadTGA.h"
#include <iostream>
#include <vector>
#include <string>
#include <wchar.h>
#include <Windows.h>
#include <CWideStringHelper.h>


CappProyecto::CappProyecto()
{
	Log << "CAppProyecto3" << endl;
	myWorld = new CWorld(getOpenGLRenderer());
}

CappProyecto::CappProyecto(int window_width, int window_height) : 
	CApp(window_width, window_height)
{
	Log << "constructor prron" << endl;
	myWorld = new CWorld(getOpenGLRenderer());
}

CappProyecto::~CappProyecto()
{
	Log << "Destructor: ~CappProyecto()" << endl;
	getOpenGLRenderer()->freeGraphicsMemoryForObject(&pgrid->shaderid, &pgrid->vaoID);
}

void CappProyecto::onMouse(float deltaX, float deltaY)
{
	/*CCamera* cam = getcamara();

	if (cam != NULL) 
	{
		cam->move(deltaX, deltaY);
	}*/
}

void CappProyecto::run()
{
	// Check if CGameWindow object and window library been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPPPARCIAL2_WINDOW_TITLE))
		{
			if(!myWorld->inicializado)
			{
				if (inicialize() == false)
				{
					cout << "error en la concha de la lora" << endl;
				}
			}

			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.15f, 0.75f, 0.75f);
			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());
			// Initialize a test cube
			//getOpenGLRenderer()->initializeTestObjects();

			// Create our menu (add all menu items)
			if (!initializeMenu())
			{
				return;
			}

			// Enter main loop
			Log << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

bool CappProyecto::initializeMenu()
{
	Log << "CAppParcial2::initializeMenu()" << endl;

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

	if (getMenu() != NULL)
	{
		CGameMenu *const menu = getMenu();

		unsigned int menuShaderProgramId = 0;
		unsigned int textureObjectId = 0;
		unsigned int vaoMenuItemId = 0;
		int colorUniformLocation = -1;
		int textureUniformLocation = -1;
		bool generatedMenuItemGeometry = false;
		float currentX = 0.65f, currentY = 0.8f;
		float menuItemHeight = 0.2f;
		float deltaY = 0.25f;
		float UV[8];

		// Create a shader program to use for the menu
		if (!getOpenGLRenderer()->createShaderProgram(
			&menuShaderProgramId,
			resourceFilenameVS.c_str(),
			resourceFilenameFS.c_str()))
		{
			return false;
		}

		// Set the generated shader program in the menu object
		menu->setShaderProgramId(menuShaderProgramId);

		TGAFILE tgaFile;
		tgaFile.imageData = NULL;

		if (LoadTGAFile(MENU_TEXTURE_FILE, &tgaFile))
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
			if (!getOpenGLRenderer()->createTextureObject(
				&textureObjectId,
				tgaFile.imageData,
				tgaFile.imageWidth,
				tgaFile.imageHeight
			))
			{
				return false;
			}

			// Set the generated texture object in the menu object
			menu->setTextureObjectId(textureObjectId);

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

		std::vector<std::string> menuOptions;
		menuOptions.push_back("Load 3D Model");
		menuOptions.push_back("Options");
		menuOptions.push_back("Exit");

		UV[0] = 0.01f;  // top left U
		UV[1] = 1.0f;   // top left V
		UV[2] = 0.99f;  // top right U
		UV[3] = 1.0f;   // top right V
		UV[4] = 0.01f;  // bottom left U
		UV[5] = 0.75f;  // bottom left V
		UV[6] = 0.99f;  // bottom right U
		UV[7] = 0.75f;  // bottom right V

		for (size_t i = 0; i < menuOptions.size(); i++)
		{
			// Allocate graphics memory for menu item
			generatedMenuItemGeometry = getOpenGLRenderer()->allocateGraphicsMemoryForMenuItem(
				currentX,
				currentY,
				menuItemHeight,
				UV,
				&menuShaderProgramId,
				&vaoMenuItemId,
				&colorUniformLocation,
				&textureUniformLocation);

			// If operation failed
			if (!generatedMenuItemGeometry)
			{
				menu->cleanupGraphicsObjects(getOpenGLRenderer());
				return false;
			}

			menu->setColorUniformLocation(colorUniformLocation);
			menu->setTextureUniformLocation(textureUniformLocation);

			menu->addMenuItem(menuOptions[i].c_str(), currentX, currentY, vaoMenuItemId);
			currentY -= deltaY;

			UV[1] -= 0.25f;
			UV[3] -= 0.25f;
			UV[5] -= 0.25f;
			UV[7] -= 0.25f;

			// Custom hack, texture used is the same for the exam, but the "exit" option is the 4th, not 3rd, so increment twice
			if (i == 1)
			{
				UV[1] -= 0.25f;
				UV[3] -= 0.25f;
				UV[5] -= 0.25f;
				UV[7] -= 0.25f;
			}
		}

		return true;
	}

	return false;
    return true;
}

void CappProyecto::update(double deltaTime)
{
	/*double degreesToRotate = 0.0;

	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;

	// Calculate degrees to rotate
	degreesToRotate = m_rotationSpeed * (deltaTime / 1000.0); // degrees = rotation speed * delta time (convert delta time from milliseconds to seconds)

															  //comente esto para que el objeto no rotara y para mover el objeto mas facil
	m_objectRotation += degreesToRotate;	                    // accumulate rotation degrees

																// Reset rotation if needed
	while (m_objectRotation > 360.0)
	{
		m_objectRotation -= 360.0;
	}
	if (m_objectRotation < 0.0)
	{
		m_objectRotation -= 0.0;
	}*/
}

void CappProyecto::render()
{
	myWorld->render();
}

bool CappProyecto::inicialize()
{
	if (myWorld->init())
	{
		return true;
	}
	else return false;
}

void CappProyecto::inicialized()
{

}



