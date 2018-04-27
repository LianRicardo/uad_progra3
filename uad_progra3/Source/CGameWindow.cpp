#include "../stdafx.h"

// include glad *before* glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Include/CAppParcial2.h"

#include <iostream>
using namespace std;

#include "../Include/CGameWindow.h"
#include "../Include/CApp.h"

// Initialize static member variables
bool CGameWindow::requestF1 = false;
bool CGameWindow::requestF2 = false;
bool CGameWindow::requestF3 = false;
bool CGameWindow::requestF4 = false;
bool CGameWindow::requestF5 = false;
bool CGameWindow::requestF6 = false;
bool CGameWindow::requestF7 = false;
bool CGameWindow::requestF8 = false;
bool CGameWindow::requestF9 = false;
bool CGameWindow::requestF10 = false;
bool CGameWindow::requestF11 = false;
bool CGameWindow::requestF12 = false;
bool CGameWindow::requestMouseMove = false;

bool CGameWindow::requestExecuteAction = false;
bool CGameWindow::requestSelectNextMenuItem = false;
bool CGameWindow::requestSelectPrevMenuItem = false;
bool CGameWindow::requestArrowUp = false;
bool CGameWindow::requestArrowDown = false;
bool CGameWindow::requestArrowLeft = false;
bool CGameWindow::requestArrowRight = false;
int  CGameWindow::keyMods = 0;

int  CGameWindow::newWidth = 0;
int  CGameWindow::newHeight = 0;

CVector3 CGameWindow::lastMousePos = { 0,0,0 };
CVector3 CGameWindow::cursorMovement = { 0,0,0 };

/* Default constructor
*/
CGameWindow::CGameWindow(COpenGLRenderer * renderer) :
	m_ReferenceRenderer{ renderer },
	m_Width{ CGameWindow::DEFAULT_WINDOW_WIDTH },
	m_Height{ CGameWindow::DEFAULT_WINDOW_HEIGHT },
	m_InitializedGLFW{ false }
{
	initializeGLFW();
}

/* Constructor with specific width/height
*/
CGameWindow::CGameWindow(COpenGLRenderer * renderer, int width, int height) :
	m_ReferenceRenderer{ renderer },
	m_Width{ width },
	m_Height{ height },
	m_InitializedGLFW{ false }
{
	initializeGLFW();
}

/* Destructor
*/
CGameWindow::~CGameWindow()
{
	glfwTerminate();
}

/* Initialize GLFW library
*/
void CGameWindow::initializeGLFW()
{
	/* Initialize the library */
	if (glfwInit())
	{
		m_InitializedGLFW = true;
		Log << "Initialized GLFW library" << endl;

		/* Set hints for new window */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // We want OpenGL 4.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OLD FLAG, don't need it because we're asking for CORE profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}
	else
	{
		Log << "Unable to initialize GLFW library" << endl;
	}
}

/* Create actual window
*/
bool CGameWindow::create(const char *windowTitle)
{
	if (m_Width <= 0 || m_Height <= 0)
	{
		Log << "Invalid window size" << std::endl;
		return false;
	}

	if (m_ReferenceRenderer == NULL)
	{
		Log << "OpenGL renderer is NULL" << endl;
		return false;
	}

	m_WindowTitle.append(windowTitle);

	/* Create a window */
	m_Window = glfwCreateWindow(m_Width, m_Height, windowTitle, NULL, NULL);

	/* If the window cannot be created, return */
	if (!m_Window)
	{
		Log << "Could not create GLFW Window" << endl;
		glfwTerminate();
		return false;
	}

	/* Set the callback for resizing the window */
	glfwSetFramebufferSizeCallback(m_Window, resizeCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);

	/* Load all OpenGL functions with GLAD using the glfw loader function */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log << "Failed to initialize OpenGL context (using glad)" << std::endl;
		return false;
	}

	/* Display OpenGL version and OpenGL Shading Language version */
	Log << "OpenGL version: " << m_ReferenceRenderer->getOpenGLString(GL_VERSION) << endl; // GLVersion.major, GLVersion.minor
	Log << "GLSL version: " << m_ReferenceRenderer->getOpenGLString(GL_SHADING_LANGUAGE_VERSION) << endl;

	const GLFWvidmode* view = glfwGetVideoMode(glfwGetPrimaryMonitor());

	/* Capture ESC key */
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

	/* Keyboard callback */
	glfwSetKeyCallback(m_Window, keyboardCallback);

	/* Mouse callback*/
	glfwSetCursorPosCallback(m_Window, mouseCallback);

	/* Hides mouse */
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Set window to pos */
	glfwSetWindowPos(m_Window, 10, (view->height - m_Height) / 2);

	/* Mouse Button callbak */
	glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);


	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	GetWindowRect(consoleWindow, &r);
	SetWindowPos(consoleWindow, 0, 10 + m_Width + 10, (view->height - m_Height) / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	return true;
}

/*
* This is the main loop, it was called from the run() method of the object derived from the CApp base class.
* This method won't return to the caller until it's done processing, but the Menu and Renderer are not part
* of this class, they're part of the CApp (or derived) class. In order to make this work, when CApp (or derived)
* object calls this main loop, IT PASSES A POINTER TO ITSELF to this CGameWindow object, so we can access the
* public methods to interact with it.
*/
void CGameWindow::mainLoop(void *appPointer)
{
	// Get mouse stuff
	double currMouseX;
	double currMouseY;

	// Variables for time-based animation
	double last_time = 0;
	double dt = 1000 / 60;  // constant dt step of 1 frame every 60 seconds
	double accumulator = 0;
	double current_time, delta_time, one_second = 0;
	double PCFreq = 0.0;
	double fps = 0.0;
	__int64 CounterStart = 0;
	int numFramesRendered = 0;
	LARGE_INTEGER li;

	if (m_Window == NULL || appPointer == NULL || m_ReferenceRenderer == NULL)
		return;

	Log << "CGameWindow::mainLoop()" << endl;

	m_ReferenceRenderer->setViewport(m_Width, m_Height);
	m_ReferenceRenderer->enableDepthTest();

	if (!QueryPerformanceFrequency(&li))
	{
		Log << "QueryPerformanceFrequency failed!\n";
		return;
	}

	PCFreq = double(li.QuadPart) / 1000.0;
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
	last_time = double(li.QuadPart - CounterStart) / PCFreq;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_Window))
	{
		numFramesRendered++;

		/* Clear color and depth buffer */
		m_ReferenceRenderer->clearScreen();

		/* Process user input */
		processInput(appPointer);

		/* Time-based animation using a high-performance counter */
		// Good example of frame-based animation vs time-based animation: http://blog.sklambert.com/using-time-based-animation-implement/
		QueryPerformanceCounter(&li);
		current_time = double(li.QuadPart - CounterStart) / PCFreq;
		delta_time = current_time - last_time; // Calculate elapsed time
		last_time = current_time;             // Update last time to be the current time
		accumulator += delta_time;

		if (delta_time > 0.0)
		{
			accumulator += delta_time;

			while (accumulator >= dt) {
				/* Update */
				((CApp *)appPointer)->update(dt);

				accumulator -= dt;
			}

			// Calculate FPS
			one_second += delta_time;
			if (one_second > 1000.0)
			{
				fps = (numFramesRendered / (one_second / 1000.0));
				one_second -= 1000.0;
				//cout << "FPS: " << fps << endl;
				numFramesRendered = 0;
			}
		}

		/* Render */
		((CApp *)appPointer)->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	/* Cleanup GLFW window */
	glfwDestroyWindow(m_Window);
}

/*
*/
void CGameWindow::resizeCallback(GLFWwindow * window, int width, int height)
{
	CGameWindow::newWidth = width;
	CGameWindow::newHeight = height;
}

/*
*/
void CGameWindow::keyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		// Save key mods (shift, alt, ctrl)
		CGameWindow::keyMods = mods;

		switch (key)
		{
		case GLFW_KEY_F1:
			CGameWindow::requestF1 = true;
			break;
		case GLFW_KEY_F2:
			CGameWindow::requestF2 = true;
			break;
		case GLFW_KEY_F3:
			CGameWindow::requestF3 = true;
			break;
		case GLFW_KEY_F4:
			CGameWindow::requestF4 = true;
			break;
		case GLFW_KEY_F5:
			CGameWindow::requestF5 = true;
			break;
		case GLFW_KEY_F6:
			CGameWindow::requestF6 = true;
			break;
		case GLFW_KEY_F7:
			CGameWindow::requestF7 = true;
			break;
		case GLFW_KEY_F8:
			CGameWindow::requestF8 = true;
			break;
		case GLFW_KEY_F9:
			CGameWindow::requestF9 = true;
			break;
		case GLFW_KEY_F10:
			CGameWindow::requestF10 = true;
			break;
		case GLFW_KEY_F11:
			CGameWindow::requestF11 = true;
			break;
		case GLFW_KEY_F12:
			CGameWindow::requestF12 = true;
			break;
			// ARROW DOWN key selects the next menu item if menu is active, application-specific otherwise
		case GLFW_KEY_DOWN:
			CGameWindow::requestSelectNextMenuItem = true;
			CGameWindow::requestArrowDown = true;
			break;
			// ARROW UP key selects the prev menu item if menu is active, application-specific otherwise
		case GLFW_KEY_UP:
			CGameWindow::requestSelectPrevMenuItem = true;
			CGameWindow::requestArrowUp = true;
			break;
			// ARROW LEFT, app-specific
		case GLFW_KEY_LEFT:
			CGameWindow::requestArrowLeft = true;
			break;
			// ARROW RIGHT, app-specific
		case GLFW_KEY_RIGHT:
			CGameWindow::requestArrowRight = true;
			break;
			// ARROW RIGHT, app-specific

			// ENTER key executes the current menu item action
		case GLFW_KEY_ENTER:
			CGameWindow::requestExecuteAction = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		// Clear key modifiers
		CGameWindow::keyMods = 0;

		switch (key)
		{
		case GLFW_KEY_UP:
			CGameWindow::requestArrowUp = false;
			break;
		case GLFW_KEY_DOWN:
			CGameWindow::requestArrowDown = false;
			break;
		case GLFW_KEY_LEFT:
			CGameWindow::requestArrowLeft = false;
			break;
		case GLFW_KEY_RIGHT:
			CGameWindow::requestArrowRight = false;
			break;
		}
	}
}

void CGameWindow::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout << lastMousePos.getX() << " ";
		std::cout << lastMousePos.getY() << " ";
		std::cout << lastMousePos.getY() << " ";
		std::cout << std::endl;
	}
}

void CGameWindow::mouseCallback(GLFWwindow * window, double xpos, double ypos)
{
	if (xpos != 0 && ypos != 0)
	{
		CGameWindow::requestMouseMove = true;

		auto last = CGameWindow::lastMousePos;
		CVector3 nPos(xpos, ypos, 0);
		CGameWindow::cursorMovement = nPos - last;
		CGameWindow::lastMousePos = nPos;
	}
	else CGameWindow::requestMouseMove = false;
}

/*
*/
void CGameWindow::processInput(void *appPointer)
{
	if (CGameWindow::newWidth > 0 && CGameWindow::newHeight > 0 && m_ReferenceRenderer != NULL)
	{
		m_Width = CGameWindow::newWidth;
		m_Height = CGameWindow::newHeight;
		m_ReferenceRenderer->setViewport(m_Width, m_Height);
		CGameWindow::newWidth = 0;
		CGameWindow::newHeight = 0;
	}

	if (m_Window != NULL)
	{
		// F1 key always toggles the menu on/off
		if (CGameWindow::requestF1)
		{
			if (((CApp *)appPointer)->isMenuActive())
			{
				((CApp *)appPointer)->setMenuActive(false);
			}
			else
			{
				((CApp *)appPointer)->setMenuActive(true);
			}
			CGameWindow::requestF1 = false;
		}
		// F12 key always closes the app
		if (CGameWindow::requestF12)
		{
			glfwSetWindowShouldClose(m_Window, true);
			CGameWindow::requestF12 = false;
		}

		// F2..F11 keys are generic
		if (CGameWindow::requestF2)
		{
			((CApp *)appPointer)->onF2(CGameWindow::keyMods);
			CGameWindow::requestF2 = false;
		}
		if (CGameWindow::requestF3)
		{
			((CApp *)appPointer)->onF3(CGameWindow::keyMods);
			CGameWindow::requestF3 = false;
		}
		if (CGameWindow::requestF4)
		{
			((CApp *)appPointer)->onF4(CGameWindow::keyMods);
			CGameWindow::requestF4 = false;
		}
		if (CGameWindow::requestF5)
		{
			((CApp *)appPointer)->onF5(CGameWindow::keyMods);
			CGameWindow::requestF5 = false;
		}
		if (CGameWindow::requestF6)
		{
			((CApp *)appPointer)->onF6(CGameWindow::keyMods);
			CGameWindow::requestF6 = false;
		}
		if (CGameWindow::requestF7)
		{
			((CApp *)appPointer)->onF7(CGameWindow::keyMods);
			CGameWindow::requestF7 = false;
		}
		if (CGameWindow::requestF8)
		{
			((CApp *)appPointer)->onF8(CGameWindow::keyMods);
			CGameWindow::requestF8 = false;
		}
		if (CGameWindow::requestF9)
		{
			((CApp *)appPointer)->onF9(CGameWindow::keyMods);
			CGameWindow::requestF9 = false;
		}
		if (CGameWindow::requestF10)
		{
			((CApp *)appPointer)->onF10(CGameWindow::keyMods);
			CGameWindow::requestF10 = false;
		}
		if (CGameWindow::requestF11)
		{
			((CApp *)appPointer)->onF11(CGameWindow::keyMods);
			CGameWindow::requestF11 = false;
		}

		// If menu is active, check the menu-specific keys
		if (((CApp *)appPointer)->isMenuActive())
		{
			// On Enter, execute action if Menu is active
			if (CGameWindow::requestExecuteAction)
			{
				((CApp *)appPointer)->executeMenuAction();

				CGameWindow::requestExecuteAction = false;

				((CApp *)appPointer)->setMenuActive(false);
			}
			// Arrow down selects the next menu item
			else if (CGameWindow::requestSelectNextMenuItem)
			{
				((CApp *)appPointer)->selectNextMenuItem();

				CGameWindow::requestSelectNextMenuItem = false;
			}
			// Arrow up selects the prev menu item
			else if (CGameWindow::requestSelectPrevMenuItem)
			{
				((CApp *)appPointer)->selectPrevMenuItem();

				CGameWindow::requestSelectPrevMenuItem = false;
			}
		}
		else
		{


			CGameWindow::requestExecuteAction = false;
			CGameWindow::requestSelectNextMenuItem = false;
			CGameWindow::requestSelectPrevMenuItem = false;

			// Check the arrow keys
			if (CGameWindow::requestArrowUp)
			{
				((CApp *)appPointer)->onArrowUp(CGameWindow::keyMods);
			}
			if (CGameWindow::requestArrowDown)
			{
				((CApp *)appPointer)->onArrowDown(CGameWindow::keyMods);
			}
			if (CGameWindow::requestArrowLeft)
			{
				((CApp *)appPointer)->onArrowLeft(CGameWindow::keyMods);
			}
			if (CGameWindow::requestArrowRight)
			{
				((CApp *)appPointer)->onArrowRight(CGameWindow::keyMods);
			}

			if (CGameWindow::requestMouseMove)
			{
				((CApp *)appPointer)->onMouse(CGameWindow::cursorMovement.getX(), CGameWindow::cursorMovement.getY());
				requestMouseMove = false;
			}
		}
	}
}

/*
*/
void CGameWindow::requestWindowClose()
{
	if (m_Window != NULL && !CGameWindow::requestF12)
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
}