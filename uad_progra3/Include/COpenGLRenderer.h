#pragma once

#ifndef _OPENGL_RENDERER_H
#define _OPENGL_RENDERER_H

// include glad *before* glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MathHelper.h"

#define BUFFER_OFFSET(a) ((void*)(a))
#define MIN_CAMERA_DISTANCE 5.0f
#define MAX_CAMERA_DISTANCE 100.0f
#define MOVE_CAMERA_DELTA 1.5f

// Class for a simple OpenGL renderer targeted for OpenGL 4.3
// UAD lab PCs support it
// *NOTE: This code has been tested to work fine on NVidia cards. Radeon cards seem to behave differently...
class COpenGLRenderer
{
private:
	int m_windowWidth;
	int m_windowHeight;
	bool m_OpenGLError;

	GLint sh_ModelUniformLocation;
	GLint sh_ViewUniformLocation;
	GLint sh_ProjUniformLocation;
	GLint sh_colorUniformLocation;

	float m_cameraDistance; // Distance from camera view point to target point, expressed in OpenGL units

	// TEST OBJECT VARS
	// When no 3D object is loaded, we display a test object (spinning cube)
	// ===========================
	GLint sh_TestPositionAttribLocation;
	GLint sh_TestColorAttribLocation;

	GLuint mTestshaderProgramID;
	GLuint mVertexPositionArrayObjectID;
	GLuint mVertexPositionBuffer;
	GLuint mVertexColorBuffer;
	GLuint mIndexBuffer;
	// ===========================

	//
	void setCurrentVertexAttribPointer(int vertexShaderAttribPos, int numComponents, int type) const;

	// This method is internally called by allocateGraphicsMemoryForObject(), (that's why it's a private method).
	//
	// There's no easy way to render multi-indexed arrays (one index for vertex, one index for normal, one index for UV coords... but that's how the info
	// is saved in the .obj format), 
	// so this method duplicates some vertices in order to render correctly.
	// The geometry created by this method is used to allocate the graphics card memory.
	// The caller can discard the geometry if it's not going to be used for anything else...
	bool generateRenderGeometry(
		GLfloat *vertices, int numVertices,
		GLfloat *normals, int numNormals,
		GLfloat *UVcoords, int numUVCoords,
		int numIndicesVert,
		unsigned short *indicesVertices,
		unsigned short *indicesNormals, 
		unsigned short *indicesUVCoords, 
		GLfloat *finalVertices,
		GLfloat *finalNormals,
		GLfloat *finalUVCoords,
		int *numTriangles
	);

	//
	bool useShaderProgram(unsigned int *shaderProgramId) const;

	//
	GLuint generateVertexArrayObjectID() const;

	//
	GLuint generateBufferObjectID(GLfloat * const vertices, int numVertices) const;

	//
	void deleteBufferObject(GLuint *id);

	//
	void deleteVertexArrayObject(GLuint *id);

public:
	// Constructor and Destructor
	COpenGLRenderer();
	~COpenGLRenderer();

	// =================================================================
	// Allocates graphics memory for a given 3D object 
	// =================================================================
	bool allocateGraphicsMemoryForObject(
		unsigned int *shaderProgramId,
		const char *vertexShader, 
		const char *fragmentShader,
		unsigned int *vertexArrayObjectID, 
		GLfloat *vertices, int numVertices,
		GLfloat *normals, int numNormals,
		GLfloat *UVcoords, int numUVCoords,
		unsigned short *indicesVertices, int numIndicesVert,
		unsigned short *indicesNormals, int numIndicesNormals,
		unsigned short *indicesUVCoords, int numIndicesUVCoords);

	// =================================================================
	// Free graphics memory for a given 3D object 
	// =================================================================
	bool freeGraphicsMemoryForObject(
		unsigned int *shaderProgramId, 
		unsigned int *vertexArrayObjectID);

	// =================================================================
	// Allocates graphics memory for a menu item (a quad)
	// We don't allocate the memory for all menu items at once because
	// we change the color (GLSL uniform) for the currently selected menu item
	// =================================================================
	bool allocateGraphicsMemoryForMenuItem(
		float topX, float topY, float menuItemHeight,
		float *uvCoords,
		unsigned int *shaderProgramId,
		unsigned int *vertexArrayObjectID,
		int *colorUniformLocation,
		int *textureUniformLocation
	);

	//
	bool createShaderProgram(
		unsigned int *shaderProgramId, 
		const char *vertexShader, 
		const char *fragmentShader);

	//
	bool deleteShaderProgram(unsigned int *shaderProgramId);

	//
	bool createTextureObject(
		unsigned int *textureObjectId, 
		unsigned char *textureData,
		int width, 
		int height);

	// 
	bool renderObject(
		unsigned int *shaderProgramId, 
		unsigned int *vertexArrayObjectId, 
		int numFaces, 
		GLfloat *objectColor, 
		MathHelper::Matrix4 *objectTransformation = NULL);

	//
	bool renderMenuItem(
		unsigned int *shaderProgramId, 
		unsigned int *textureObjectId,
		unsigned int *vertexArrayObjectId,
		int *colorUniformLocation, 
		int *textureUniformLocation,
		GLfloat *menuItemColor);

	//
	void setWindowWidth(int width) { m_windowWidth = width; }
	void setWindowHeight(int height) { m_windowHeight = height; }

	//
	void renderTestObject(MathHelper::Matrix4 *objectTransformation = NULL);
	void initializeTestObjects();

	//
	bool checkOpenGLError(char *operationAttempted);

	//
	void setClearScreenColor(float r, float g, float b) { glClearColor(r, g, b, 1.0f); }

	//
	void deleteTexture(unsigned int *id);

	//
	float getCameraDistance() const { return m_cameraDistance; }
	void setCameraDistance(float d) { m_cameraDistance = d; }

	//
	void moveCamera(float direction);

	//
	void enableDepthTest() { glEnable(GL_DEPTH_TEST); }

	//
	void setViewport(int width, int height) { glViewport(0, 0, width, height); }

	//
	const GLubyte * getOpenGLString(GLenum id) { return glGetString(id); }

	//
	void clearScreen() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	//
	void drawGrid();

	//
	void drawString(unsigned int *textureObjectId, std::string &text, float x, float y, CVector3 &color);
};

#endif // !_OPENGL_RENDERER_H

// https://www.khronos.org/opengl/wiki/Common_Mistakes