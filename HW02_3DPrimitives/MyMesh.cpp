#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	
	float radAmount = (2 * 3.14) / a_nSubdivisions;

	//AddTri(vector3(0.0f, 0.0f, 0.0f),
	//	vector3(_CMATH_::sin(3.14 / 2), _CMATH_::cos(3.14 / 2), 0.0f),
	//	vector3(_CMATH_::sin(3.14 / 2 + radAmount), _CMATH_::cos(3.14 / 2 + radAmount), 0.0f));

	for (unsigned int i = 0; i < a_nSubdivisions; i++)
	{

		AddTri(vector3(0.0f, 0.0f, -a_fHeight),
			vector3(_CMATH_::sin(radAmount * i), _CMATH_::cos(radAmount * i), 0.0f) * a_fRadius,
			vector3(_CMATH_::sin( radAmount * (i + 1)), _CMATH_::cos(radAmount * (i + 1)), 0.0f) * a_fRadius);

		AddTri(vector3(0.0f, 0.0f, 0),
			vector3(_CMATH_::sin( radAmount * (i + 1)), _CMATH_::cos(radAmount * (i + 1)), 0.0f) * a_fRadius,
			vector3(_CMATH_::sin(radAmount * i), _CMATH_::cos(radAmount * i), 0.0f)* a_fRadius);
	}


	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();


	// Replace this with your code
	float radAmount = (2 * 3.14) / a_nSubdivisions;

	std::vector<vector3> faceA;
	std::vector<vector3> faceB;

	// Create the end faces 
	for (unsigned int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 currentFaceAPoint = vector3(_CMATH_::sin(radAmount * i) * a_fRadius, _CMATH_::cos(radAmount * i) * a_fRadius, -a_fHeight / 2);
		vector3 nextFaceAPoint = vector3(_CMATH_::sin(radAmount * (i + 1)) * a_fRadius, _CMATH_::cos( radAmount * (i + 1)) * a_fRadius, -a_fHeight / 2);
		faceA.push_back(currentFaceAPoint);

		AddTri(
			vector3(0.0f, 0.0f, -a_fHeight / 2),
			currentFaceAPoint,
			nextFaceAPoint
		);

		vector3 currentFaceBPoint = vector3(_CMATH_::sin(radAmount * (i + 1)) * a_fRadius, _CMATH_::cos(radAmount * (i + 1)) * a_fRadius, a_fHeight / 2);
		vector3 nextFaceBPoint = vector3(_CMATH_::sin(radAmount * i) * a_fRadius, _CMATH_::cos(radAmount * i) * a_fRadius, a_fHeight / 2);
		faceB.push_back(currentFaceBPoint);

		AddTri(
			vector3(0.0f, 0.0f, a_fHeight / 2),
			currentFaceBPoint,
			nextFaceBPoint
		);
	}

	// Adds the sides 
	for (unsigned int i = 0; i < a_nSubdivisions; i++)
	{
		if (i + 1 < faceA.size())
		{
			AddTri(
				faceA[i],
				faceB[i],
				faceA[i + 1]
			);

			AddTri(
				faceA[i + 1],
				faceB[i],
				faceB[i + 1]
			);
		}
		else
		{
			AddTri(
				faceA[i],
				faceB[i],
				faceA[0]
			);

			AddTri(
				faceA[0],
				faceB[i],
				faceB[0]
			);
		}
		
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	float radAmount = (2 * 3.14) / a_nSubdivisions;
	
	std::vector<vector3> innerFaceA;
	std::vector<vector3> innerFaceB;

	std::vector<vector3> outerFaceA;
	std::vector<vector3> outerFaceB;

	// Create the end faces 
	for (unsigned int i = 0; i < a_nSubdivisions; i++)
	{
		// Inner 

		vector3 currentFaceAPointInner = vector3(_CMATH_::sin(radAmount * i) * a_fInnerRadius, _CMATH_::cos(radAmount * i) * a_fInnerRadius, -a_fHeight / 2);
		vector3 nextFaceAPointInner = vector3(_CMATH_::sin(radAmount * (i + 1)) * a_fInnerRadius, _CMATH_::cos(radAmount * (i + 1)) * a_fInnerRadius, -a_fHeight / 2);
		innerFaceA.push_back(currentFaceAPointInner);

		/*AddTri(
			vector3(0.0f, 0.0f, -a_fHeight / 2),
			currentFaceAPointInner,
			nextFaceAPointInner
		);*/

		vector3 currentFaceBPointInner = vector3(_CMATH_::sin(radAmount * (i + 1)) * a_fInnerRadius, _CMATH_::cos(radAmount * (i + 1)) * a_fInnerRadius, a_fHeight / 2);
		vector3 nextFaceBPointInner = vector3(_CMATH_::sin(radAmount * i) * a_fInnerRadius, _CMATH_::cos(radAmount * i) * a_fInnerRadius, a_fHeight / 2);
		innerFaceB.push_back(currentFaceBPointInner);

		/*AddTri(
			vector3(0.0f, 0.0f, a_fHeight / 2),
			currentFaceBPointInner,
			nextFaceBPointInner
		);*/


		// Outer

		vector3 currentFaceAPointOuter = vector3(_CMATH_::sin(radAmount * i) * a_fOuterRadius, _CMATH_::cos(radAmount * i) * a_fOuterRadius, -a_fHeight / 2);
		vector3 nextFaceAPoint = vector3(_CMATH_::sin(radAmount * (i + 1)) * a_fOuterRadius, _CMATH_::cos(radAmount * (i + 1)) * a_fOuterRadius, -a_fHeight / 2);
		outerFaceA.push_back(currentFaceAPointOuter);

		/*AddTri(
			vector3(0.0f, 0.0f, -a_fHeight / 2),
			currentFaceAPointOuter,
			nextFaceAPoint
		);*/

		vector3 currentFaceBPointOuter = vector3(_CMATH_::sin(radAmount * (i + 1)) * a_fOuterRadius, _CMATH_::cos(radAmount * (i + 1)) * a_fOuterRadius, a_fHeight / 2);
		vector3 nextFaceBPointOuter = vector3(_CMATH_::sin(radAmount * i) * a_fOuterRadius, _CMATH_::cos(radAmount * i) * a_fOuterRadius, a_fHeight / 2);
		outerFaceB.push_back(currentFaceBPointOuter);

		/*AddTri(
			vector3(0.0f, 0.0f, a_fHeight / 2),
			currentFaceBPointOuter,
			nextFaceBPointOuter
		);*/

	}


	// Draw faces 
	for (unsigned int i = 0; i < a_nSubdivisions; i++)
	{
		if (i + 1 < outerFaceA.size())
		{
			// Sides 

			// Outside 
			AddTri(
				outerFaceA[i],
				outerFaceB[i],
				outerFaceA[i + 1]
			);

			AddTri(
				outerFaceA[i + 1],
				outerFaceB[i],
				outerFaceB[i + 1]
			);

			// Inside 
			AddTri(
				innerFaceA[i],
				innerFaceA[i + 1],
				innerFaceB[i]
			);

			AddTri(
				innerFaceA[i + 1],
				innerFaceB[i + 1],
				innerFaceB[i]
			);


			// Ends 
			AddQuad(outerFaceA[i + 1], innerFaceA[i + 1], outerFaceA[i], innerFaceA[i]);
			AddQuad(outerFaceB[i], innerFaceB[i], outerFaceB[i + 1], innerFaceB[i + 1]);
		}
		else
		{
			// Outside 
			AddTri(
				outerFaceA[i],
				outerFaceB[i],
				outerFaceA[0]
			);

			AddTri(
				outerFaceA[0],
				outerFaceB[i],
				outerFaceB[0]
			);

			// Inside 
			AddTri(
				innerFaceA[i],
				innerFaceA[0],
				innerFaceB[i]
			);

			AddTri(
				innerFaceA[0],
				innerFaceB[0],
				innerFaceB[i]
			);

			AddQuad(outerFaceA[0], innerFaceA[0], outerFaceA[i], innerFaceA[i]);
			AddQuad(outerFaceB[i], innerFaceB[i], outerFaceB[0], innerFaceB[0]);
		}

	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();


	// Replace this with your code
	
	//float radAmountA = (2 * PI) / a_nSubdivisionsA;
	//float radAmountB = (2 * PI) / a_nSubdivisionsB;
	//float mag = (a_fOuterRadius + a_fInnerRadius) / 2; // Dis to center of circles 
	//float radius = a_fOuterRadius - a_fInnerRadius;  // Radius of the duplicated circles 

	//// The primary circle that the others are built on
	//std::vector<vector3> circleFrame;
	//// The actual circle that the geometry is stitched upon 
	//std::vector<vector3> circleConnectors; 

	//// Form a circle in data with sub A as its points 
	//for (unsigned int i = 0; i < a_nSubdivisionsA; i++)
	//{
	//	float frameDelta = PI / 2 + radAmountA * i;
	//	vector3 currentFramePoint = vector3(_CMATH_::sin(frameDelta) * mag, _CMATH_::cos(frameDelta) * mag, 0);
	//	/*vector3 nextFramePoint = vector3(_CMATH_::sin(3.14 / 2 + radAmountA * (i + 1)) * mag, _CMATH_::cos(3.14 / 2 + radAmountA * (i + 1)) * mag, 0);

	//	AddTri(
	//		vector3(0, 0, 0),
	//		currentFramePoint,
	//		nextFramePoint
	//	);*/
	//	
	//	// Along each point in this circle create a circle 
	//	for (unsigned int j = 0; j < a_nSubdivisionsB; j++)
	//	{
	//		
	//		float connectorDelta = PI / 2 + radAmountA * j;
	//		vector3 currentFaceAPoint = vector3(_CMATH_::sin(connectorDelta) * radius, 0, _CMATH_::cos(connectorDelta) * radius);
	//		vector3 nextFaceAPoint = vector3(_CMATH_::sin(3.14 / 2 + radAmountA * (j + 1)) * radius, 0, _CMATH_::cos(3.14 / 2 + radAmountA * (j + 1)) * radius);

	//		glm::mat4x4 matTemp = glm::rotate(IDENTITY_M4, (float)((frameDelta * 180) / PI), AXIS_Z);

	//		vector3 center = currentFramePoint;
	//		vector4 pos = matTemp * vector4(currentFaceAPoint, 1);
	//		vector4 posNext = matTemp * vector4(nextFaceAPoint, 1);

	//		vector3 dir = vector3(cos(frameDelta), sin(frameDelta), 0) * mag;
	//		
	//		AddTri(
	//			vector3(0,0,0),
	//			vector4(dir, 0) + pos,
	//			vector4(dir, 0) + posNext
	//		);
	//	}
	//}


	std::vector<vector3> points;
	float radAmountA = (2 * PI) / a_nSubdivisionsA;
	float radAmountB = (2 * PI) / a_nSubdivisionsB;
	float minorCircleRadius = (a_fOuterRadius - a_fInnerRadius) / 2;
	//float mag = (a_fOuterRadius + a_fInnerRadius) / 2; // Dis to center of circles 

	// How smooth is the primary circle frame that the other circles are spawned on 
	for (unsigned int i = 0; i <= a_nSubdivisionsA; i++)
	{
		float delta = radAmountA * i;
		float cosMain = _CMATH_::cos(delta);
		float sinMain = _CMATH_::sin(delta);

		// How smooth are the circles that make the tube
		for (unsigned int j = 0; j <= a_nSubdivisionsB; j++)
		{
			// Forms circles in data that get bigger then smaller as the go away from the
			// center of the tours and then loop back around 

			// Secondary circle 
			float theta = radAmountB * j;
			float sinMinor = _CMATH_::sin(theta);
			float cosMinor = _CMATH_::cos(theta);


			vector3 point = vector3(
				(a_fInnerRadius + minorCircleRadius * cosMinor) * cosMain,
				(a_fInnerRadius + minorCircleRadius * cosMinor) * sinMain,
				minorCircleRadius * sinMinor);
			
			points.push_back(point);
		}
	}
	

	for (unsigned int i = 0; i < points.size(); i++)
	{
		if (i + a_nSubdivisionsB + 1 < points.size())
		{
			/*AddTri(
					vector3(0, 0, 0),
				points[i],
				points[i + 1]
				);*/

			// Draws using quad sections 
			AddQuad(points[i + a_nSubdivisionsB], points[i + a_nSubdivisionsB + 1], points[i], points[i + 1]);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	
	float radAmount = (2 * PI) / a_nSubdivisions;
	float zDelta = (2 * a_fRadius) / a_nSubdivisions;

	std::vector<vector3> points;

	

	for (int i = 1; i < a_nSubdivisions; i++)
	{
		// Centers the sphere
		float z = i * zDelta - a_fRadius;
		float theta = radAmount * i;

		// Creates each circle layer 
		for (int j = 0; j < a_nSubdivisions; j++)
		{
			float delta = radAmount * j;
			float cos = _CMATH_::cos(delta) * _CMATH_::sin(0.5f * theta);
			float sin = _CMATH_::sin(delta) * _CMATH_::sin(0.5f * theta);

			points.push_back(vector3(cos * a_fRadius, sin * a_fRadius, z));
			//std::cout << cos << ", " << sin << ", " << z << std::endl;

		}
	}

	// Not sure why but this one tri needs to be done manually 
	// Could not figure out before due time :(
	AddTri(
		points[0],
		points[a_nSubdivisions],
		points[a_nSubdivisions - 1]
	);
	
	for (int i = 0; i < points.size(); i++)
	{
		if (i + a_nSubdivisions + 1 < points.size())
		{
			// Draws using quad sections 
			AddQuad(points[i], points[i + 1], points[i + a_nSubdivisions], points[i + a_nSubdivisions + 1]);

			
		}
		else if (i + a_nSubdivisions < points.size())
		{
			AddQuad(points[i], points[i + 1], points[i + a_nSubdivisions], points[0]);
		}
		else if (i + 1 < a_nSubdivisions)
		{
			AddQuad(points[i], points[i + 1], points[0], points[0 + 1]);
		}
	}

	// Connecting ends
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i + 1 < a_nSubdivisions)
		{
			AddTri(
				vector3(0, 0, -a_fRadius),
				points[i + 1],
				points[i]
			);

			AddTri(
				vector3(0, 0, a_fRadius),
				points[points.size() - (i + 2)],
				points[points.size() - (i + 1)]
			);
		}
		else
		{
			// Loops 

			AddTri(
				vector3(0, 0, -a_fRadius),
				points[0],
				points[i]
			);

			AddTri(
				vector3(0, 0, a_fRadius),
				points[points.size() - 1],
				points[points.size() - (i + 1)]
			);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}