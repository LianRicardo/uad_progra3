#include "../stdafx.h"

#include "windows.h"
#include "../Include/Globals.h"
#include "../Include/CAppParcial2.h"
//#include "../Include/C3DModel.h
#include "../Include/OBJLoaderDLL.h"
#include "../Include/LoadTGA.h"
#include <iostream>
#include <vector>
#include <string>
#include <wchar.h>
#include <Windows.h>
using namespace std;


/* */

CAppParcial2::CAppParcial2() : 
	m_p3DModel(NULL),
	m_currentDeltaTime{ 0.0 },
	m_objectRotation{ 0.0 },
	m_objectPosition{ 0.0f, 0.0f, 0.0f },
	m_rotationSpeed{ DEFAULT_ROTATION_SPEED }
{
	cout << "Constructor: CAppParcial2()" << endl;
}

/* */
CAppParcial2::CAppParcial2(int window_width, int window_height) : 
	CApp(window_width, window_height),
	m_p3DModel(NULL),
	m_currentDeltaTime{ 0.0 },
	m_objectRotation{ 0.0 },
	m_objectPosition{ 0.0f, 0.0f, 0.0f },
	m_rotationSpeed{ DEFAULT_ROTATION_SPEED }
{
	cout << "Constructor: CAppParcial2(int window_width, int window_height)" << endl;
}

/* */
CAppParcial2::~CAppParcial2()
{
	cout<< "Destructor: ~CAppParcial2()" << endl;
	unloadCurrent3DModel();
}

/* */
void CAppParcial2::run()
{
	// Check if CGameWindow object and window library been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPPPARCIAL2_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.15f, 0.75f, 0.75f);
			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());
			// Initialize a test cube
			getOpenGLRenderer()->initializeTestObjects();

			// Create our menu (add all menu items)
			if (!initializeMenu())
			{
				return;
			}

			// Enter main loop
			cout << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

/* */
bool CAppParcial2::initializeMenu()
{
	cout << "CAppParcial2::initializeMenu()" << endl;

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
			VERTEX_SHADER_MENU,
			FRAGMENT_SHADER_MENU))
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
}

/* */
void CAppParcial2::update(double deltaTime)
{
	double degreesToRotate = 0.0;

	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;

	// Calculate degrees to rotate
	degreesToRotate   = m_rotationSpeed * (deltaTime / 1000.0); // degrees = rotation speed * delta time (convert delta time from milliseconds to seconds)

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
	}
}

/* */
void CAppParcial2::render()
{
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL && menu->isInitialized() && menu->isActive())
	{
		menu->render(getOpenGLRenderer());
	}
	else // Otherwise, render active object if loaded (or test cube if no object is loaded)
	{
		// White 
		float color[3] = {0.95f, 0.95f, 0.95f};

		if (m_p3DModel != NULL && m_p3DModel->isInitialized())
		{
			// convert total degrees rotated to radians;
			double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;
			// Get a matrix that has both the object rotation and translation
			MathHelper::Matrix4 modelMatrix   = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);

			getOpenGLRenderer()->renderObject(
				m_p3DModel->getShaderProgramId(),
				m_p3DModel->getGraphicsMemoryObjectId(),
				m_p3DModel->getNumFaces(), 
				color,
				&modelMatrix
			);
		}
		else
		{
			double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

			// Get a matrix that has both the object rotation and translation
			MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);

			// No model loaded, show test cube
			getOpenGLRenderer()->renderTestObject(&m_currentDeltaTime);
		}
	}
}

/* */
bool CAppParcial2::load3DModel(const char * const filename)
{
	// Unload any current 3D model
	unloadCurrent3DModel();

	// Toma el tama�o necesario para crear el arreglo de caracteres.  strlen documentaci�n  https://msdn.microsoft.com/en-us/library/78zh94ax.aspx?f=255&MSPPError=-2147217396
	int num_chars = MultiByteToWideChar(CP_UTF8, 0, filename, (int)strlen(filename), NULL, 0);

	//Genera un string del tama�o especificado por usuario y lo llena con caracteres del alfabeto    http://www.cplusplus.com/reference/cstdlib/malloc/ 
	//wchar_t* wstrTo = (wchar_t*)malloc((num_chars + 1) * sizeof(wchar_t));
	wchar_t* wstrTo = new wchar_t[num_chars + 1];


	// Convierte la linea de caracteres y lo almacena en la hecha previamente
	MultiByteToWideChar(CP_UTF8, 0, &filename[0], (int)strlen(filename), wstrTo, num_chars);
	wstrTo[num_chars] = '\0';
	
	bool loaded = false;

	// Create new 3D object
	m_p3DModel = C3DModel::Load(wstrTo);

	if(m_p3DModel!=	NULL)
	{
		// Load object from file
		loaded = m_p3DModel->isInitialized();
	}
	else
	{
		cout << "error no se pudo cargar el archivo" << endl;
	}

	if (loaded)
	{
		// Allocate graphics memory for object
		loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
			m_p3DModel->getShaderProgramId(),
			VERTEX_SHADER_3D_OBJECTS,
			FRAGMENT_SHADER_3D_OBJECTS,
			m_p3DModel->getGraphicsMemoryObjectId(),
			m_p3DModel->getModelVertices(),
			m_p3DModel->getNumVertices(),
			m_p3DModel->getModelNormals(),
			m_p3DModel->getNumNormals(),
			m_p3DModel->getModelUVCoords(),
			m_p3DModel->getNumUVCoords(),
			m_p3DModel->getModelVertexIndices(),
			m_p3DModel->getNumFaces(),
			m_p3DModel->getModelNormalIndices(),
			((m_p3DModel)?(m_p3DModel->getNumFaces()):0),
			m_p3DModel->getModelUVCoordIndices(),
			((m_p3DModel)?(m_p3DModel->getNumFaces()):0)
		);

		// If error ocurred, cleanup memory
		if (!loaded)
		{
			unloadCurrent3DModel();
		}
	}

	return loaded;
}

/* */
void CAppParcial2::unloadCurrent3DModel()
{
	if (m_p3DModel != NULL)
	{
		// Free up graphics memory
		getOpenGLRenderer()->freeGraphicsMemoryForObject(
			m_p3DModel->getShaderProgramId(),
			m_p3DModel->getGraphicsMemoryObjectId()
		);

		// Delete 3D object
		delete m_p3DModel;
		m_p3DModel = NULL;
	}
}

/* */
void CAppParcial2::onF2(int mods)
{
	std::wstring wideStringBuffer = L"buffer";
	wideStringBuffer.resize(MAX_PATH);

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner   = NULL;
	ofn.lpstrFilter = L"Obj Files\0*.obj\0All files\0*.*\0";
	ofn.lpstrFile   = &wideStringBuffer[0];
	ofn.nMaxFile    = MAX_PATH;
	ofn.lpstrTitle  = L"Select a model file";
	ofn.Flags       = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wideStringBuffer[0], (int)wideStringBuffer.size(), NULL, 0, NULL, NULL);
		std::string multibyteString(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wideStringBuffer[0], (int)wideStringBuffer.size(), &multibyteString[0], size_needed, NULL, NULL);
		cout << "Filename to load: " << multibyteString.c_str() << endl;

		if (!load3DModel(multibyteString.c_str()))
		{
			cout << "Unable to load 3D model" << endl;
		}
	}
}

/* */
void CAppParcial2::onF3(int mods)
{
	// Check BITWISE AND to detect shift/alt/ctrl
	if (mods & KEY_MOD_SHIFT)
	{
		moveCamera(-1.0f);
	}
	else
	{
		moveCamera(1.0f);
	}
}

void CAppParcial2::onF4(int mods)
{
	_STARTUPINFOW notep = { sizeof(_STARTUPINFOW) };
	_PROCESS_INFORMATION procInfo;
	TCHAR b[] = TEXT("notepad");
	CreateProcess(NULL, b, NULL, NULL, false, NULL, NULL, NULL, &notep, &procInfo);
}

void CAppParcial2::onArrowUp(int mods)
{
	m_objectPosition += m_Up;
}

void CAppParcial2::onArrowDown(int mods)
{
	m_objectPosition += m_Down;
}

void CAppParcial2::onArrowLeft(int mods)
{
	m_objectPosition += m_Left;
}

void CAppParcial2::onArrowRight(int mods)
{
	m_objectPosition += m_Right;
}

void CAppParcial2::onMouseMove(float deltaX, float deltaY)
{
	if (deltaX < 100.0f && deltaY < 100.0f)
	{
		float posiciones[3];
		m_objectPosition.getValues(posiciones);
		posiciones[0] -= deltaX * DEFAULT_SPEED;
		posiciones[2] -= deltaY * DEFAULT_SPEED;
		m_objectPosition.setValues(posiciones);
	}
}

/* */
void CAppParcial2::moveCamera(float direction)
{
	if (getOpenGLRenderer() != NULL)
	{
		getOpenGLRenderer()->moveCamera(direction);
	}
}

/* */
void CAppParcial2::executeMenuAction()
{
	if (getMenu() != NULL)
	{
		int option = getMenu()->getSelectedMenuItemNumber();

		switch (option)
		{
		case 1:
			onF2(0);
			break;
		case 2:
			// Not implemented
			cout << "<MENU OPTION NOT IMPLEMENTED>" << endl;
			break;
		case 3:
			if (getGameWindow() != NULL)
			{
				getGameWindow()->requestWindowClose();
			}
			break;
		}
	}
}