#include "../stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "../Include/C3DModel_obj.h"

C3DModel_obj::~C3DModel_obj()
{
	cout << "Destructor: C3DModel_obj()" << endl;
	reset();
}

C3DModel_obj::C3DModel_obj()
	: m_vertices(nullptr) ,
	m_normals(nullptr) ,
	m_UVCoords(nullptr)
{
		cout << "corriendo constructor del obj" << endl;
}

bool C3DModel_obj::readFile(const char * filename, bool countOnly)
{
	ifstream infile;
	string lineBuffer;
	bool readFileOk = true;
	int lineNumber = 0;

	infile.open(filename);

	while (!infile.eof())
	{
		getline(infile, lineBuffer);
		lineNumber++;

		if (!(this->parseLine(lineBuffer, countOnly, lineNumber)))
		{
			readFileOk = false;
			break;
		}
		// cout << lineBuffer << endl;
	}

	infile.close();

	return readFileOk;
}

bool C3DModel_obj::loadFromFile(const char * const filename)
{
	bool readFileOk = false;

	// Free any previous resources
	reset();

	// First pass is to count the number of vertices, normals, UVs, faces
	readFileOk = readFile(filename, true);

	// Display count
	cout << "Finished reading 3D model" << endl;
	cout << "Vertices: " << m_numVertices << endl;
	cout << "Normals: " << m_numNormals << endl;
	cout << "UVCoords: " << m_numUVCoords << endl;
	cout << "Faces: " << m_numFaces << endl;

	if (readFileOk)
	{
		// Check for MAX number of faces
		if (m_numVertices >= 65535 || m_numNormals >= 65535 || m_numUVCoords >= 65535)
		{
			cout << "Error: object cannot have more than 65535 vertices" << endl;
			cout << "Object attempted to load has: " << m_numVertices << " vertices" << endl;
			return false;
		}

		// Allocate memory for the arrays
		m_vertices = new CVector3[m_numVertices];
		m_verticesRaw = new float[m_numVertices * 3];
		m_normals = new CVector3[m_numNormals];
		m_normalsRaw = new float[m_numNormals * 3];
		m_UVCoords = new CVector3[m_numUVCoords];
		m_uvCoordsRaw = new float[m_numUVCoords * 2];
		m_vertexIndices = new unsigned short[m_numFaces * 3];
		m_normalIndices = new unsigned short[m_numFaces * 3];
		m_UVindices = new unsigned short[m_numFaces * 3];

		// Zero-out indices arrays
		memset(m_vertexIndices, 0, sizeof(unsigned short) * m_numFaces * 3);
		memset(m_normalIndices, 0, sizeof(unsigned short) * m_numFaces * 3);
		memset(m_UVindices, 0, sizeof(unsigned short) * m_numFaces * 3);
		memset(m_verticesRaw, 0, sizeof(float) * m_numVertices * 3);
		memset(m_normalsRaw, 0, sizeof(float) * m_numNormals * 3);
		memset(m_uvCoordsRaw, 0, sizeof(float) * m_numUVCoords * 2);

		// Second pass is to read the data
		readFileOk = readFile(filename, false);

		if (readFileOk)
		{
			m_Initialized = true;
		}
	}
	else
	{
		cout << "Error ocurred while reading 3D model." << endl;
	}

	return readFileOk;
}

bool C3DModel_obj::parseLine(std::string line, bool countOnly, int lineNumber)
{
	bool parsed = false;
	bool unrecognizedLine = false;

	bool readingVertex = false;
	bool readingNormal = false;
	bool readingUV = false;
	bool readingFace = false;

	char *nextToken = NULL;
	char *token = NULL;

	const char *delimiterToken = " \t";
	const char *delimiterFace = "/";

	int currentToken = 0;
	int numTokens = 0;
	int numExpectedTokens = 4;

	std::vector<std::string> tokens;

	token = strtok_s((char *)line.c_str(), delimiterToken, &nextToken);

	// Line without space or tab separators (most likely a null string)
	if (token == NULL)
	{
		parsed = true;
	}

	// If there are any tokens left
	while (token != NULL)
	{
		// If first token
		if (currentToken == 0)
		{
			// Vertex
			if (0 == strcmp(token, "v"))
			{
				readingVertex = true;

				if (countOnly)
				{
					m_numVertices++;
				}
			}
			// Normal
			else if (0 == strcmp(token, "vn"))
			{
				readingNormal = true;

				if (countOnly)
				{
					m_numNormals++;
				}
			}
			// Vertex texture
			else if (0 == strcmp(token, "vt"))
			{
				readingUV = true;

				if (countOnly)
				{
					m_numUVCoords++;
				}
			}
			// Face
			else if (0 == strcmp(token, "f"))
			{
				readingFace = true;

				if (countOnly)
				{
					m_numFaces++;
				}
			}
			else
			{
				// Unrecognized line
				if (countOnly)
				{
					cout << "Ignoring line #" << lineNumber << ": " << line << endl;
				}
				unrecognizedLine = true;
			}

			// If this line has an unrecognized format
			// OR If we're in count only mode and we processed the first token, 
			// break to exit method and go to next line
			if (countOnly || unrecognizedLine)
			{
				return true;
			}
		}
		else
		{
			// Add token to vector
			tokens.push_back(std::string(token));
		}

		// Read next token
		token = strtok_s(NULL, delimiterToken, &nextToken);
		currentToken++;

		// No more tokens
		if (token == NULL)
		{
			//  If we're NOT in "count only" mode
			if (!countOnly)
			{
				// Verify we have the expected number of tokens
				if (currentToken != numExpectedTokens)
				{
					cout << "Ignoring line, number of tokens doesn't match the expected." << endl;
					cout << line.c_str() << endl;
				}
				else
				{
					// Create the vertex|normal|UVcoord|face
					if (readingVertex || readingNormal || readingUV)
					{
						// Add the 3 effective tokens to the appropriate array
						float values[3];
						values[0] = (float)atof(tokens[0].c_str());
						values[1] = (float)atof(tokens[1].c_str());
						values[2] = (float)atof(tokens[2].c_str());
						parsed = true;

						if (readingVertex && m_vertices != NULL &&
							(m_currentVertex < m_numVertices) && m_numVertices > 0)
						{
							m_vertices[m_currentVertex].setValues(values);

							m_verticesRaw[(m_currentVertex * 3)] = values[0];
							m_verticesRaw[(m_currentVertex * 3) + 1] = values[1];
							m_verticesRaw[(m_currentVertex * 3) + 2] = values[2];

							m_currentVertex++;
						}
						else if (readingNormal && m_normals != NULL &&
							(m_currentNormal < m_numNormals) && m_numNormals > 0)
						{
							m_normals[m_currentNormal].setValues(values);

							m_normalsRaw[(m_currentNormal * 3)] = values[0];
							m_normalsRaw[(m_currentNormal * 3) + 1] = values[1];
							m_normalsRaw[(m_currentNormal * 3) + 2] = values[2];

							m_currentNormal++;
						}
						else if (readingUV && m_UVCoords != NULL &&
							(m_currentUV < m_numUVCoords) && m_numUVCoords > 0)
						{
							m_UVCoords[m_currentUV].setValues(values);

							m_uvCoordsRaw[(m_currentUV * 2)] = values[0];
							m_uvCoordsRaw[(m_currentUV * 2) + 1] = values[1];

							m_currentUV++;
						}
						else
						{
							parsed = false;
						}
					}
					else if (
						readingFace
						&& m_vertexIndices != NULL
						&& m_normalIndices != NULL
						&& m_UVindices != NULL
						&& (m_currentFace < (m_numFaces * 3))
						&& m_numFaces > 0
						)
					{
						// Parse the current token to extract the vertex|normal|UV index
						parsed = true;
						nextToken = NULL;
						token = NULL;

						// Loop through all 3 groups of indices, i.e:    1/3/4    3/5/2    2/3/1
						//
						// token[0] = 1/3/4
						// token[1] = 3/5/2
						// token[2] = 2/3/1
						for (int i = 0; i < 3 && i < tokens.size(); i++)
						{
							currentToken = -1;

							// Get group of indices and split it into tokens with '/' as delimiter
							token = strtok_s((char *)tokens[i].c_str(), delimiterFace, &nextToken);

							while (nextToken != NULL && *nextToken != '\0')
							{
								currentToken++;

								if (token != NULL)
								{
									switch (currentToken)
									{
									case 0:
										//m_vertexIndices[m_currentFace + i] = (unsigned short)(atoi(token));
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_vertexIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 1:
										//m_UVindices[m_currentFace + i] = (unsigned short)(atoi(token));
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_UVindices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 2:
										//m_normalIndices[m_currentFace + i] = (unsigned short)(atoi(token));
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_normalIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									}
								}

								token = strtok_s(NULL, delimiterFace, &nextToken);

								// Last token
								if (token != NULL &&
									(nextToken == NULL || (nextToken != NULL && *nextToken == '\0'))
									)
								{
									currentToken++;

									switch (currentToken)
									{
									case 0:
										//m_vertexIndices[m_currentFace + i] = (unsigned short)(atoi(token));
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_vertexIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 1:
										//m_UVindices[m_currentFace + i] = (unsigned short)(atoi(token));
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_UVindices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 2:
										//m_normalIndices[m_currentFace + i] = (unsigned short)(atoi(token));
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_normalIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									}
								}
							} // while (nextToken != NULL)
						} // for

						m_currentFace += 3;
						token = NULL;
						nextToken = NULL;
					} // reading face

				} // reading
			} // !count only
		} // No more tokens
	}
	return parsed;
}

void C3DModel_obj::reset()
{
	if (m_vertices != NULL)
	{
		cout << "deleting vertices" << endl;
		delete[] m_vertices;
		m_vertices = NULL;
	}
	if (m_normals != NULL)
	{
		cout << "deleting normals" << endl;
		delete[] m_normals;
		m_normals = NULL;
	}
	if (m_UVCoords != NULL)
	{
		cout << "deleting UV coords" << endl;
		delete[] m_UVCoords;
		m_UVCoords = NULL;
	}
}
