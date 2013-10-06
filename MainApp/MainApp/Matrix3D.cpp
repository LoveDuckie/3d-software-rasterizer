#include "stdafx.h"
#include "Vertex.h"
#include "Matrix3D.h"

// Constructors
Matrix3D::Matrix3D(void)
{
	// Declare default initialisation
	//Init(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);

	// Setting default values
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_m[i][j] = 0.0f;
		}
	}

}

Matrix3D::Matrix3D(float m01, float m02, float m03, float m04,
				   float m11, float m12, float m13, float m14,
				   float m21, float m22, float m23, float m24,
				   float m31, float m32, float m33, float m34)
{
	Init(m01,m02,m03,m04,
		 m11,m12,m13,m14,
		 m21,m22,m23,m24,
		 m31,m32,m33,m34);
}

Matrix3D::Matrix3D(const Matrix3D& m)
{
	Copy(m);
}

void Matrix3D::Copy(const Matrix3D& m)
{
	for (int i = 0; i < 4; i++)
	{
		
		for (int j = 0; j < 4; j++)
		{
			this->_m[i][j] = m._m[i][j];
		}
	}

}

//const Vertex Matrix3D::operator+(const Vertex &p) const
//{
//
//
//
//}

// Initliasation method
void Matrix3D::Init(float m01, float m02, float m03, float m04,
					float m11, float m12, float m13, float m14, 
					float m21, float m22, float m23, float m24,
					float m31, float m32, float m33, float m34)
{
	this->_m[0][0] = m01;
	this->_m[0][1] = m02;
	this->_m[0][2] = m03;
	this->_m[0][3] = m04;

	this->_m[1][0] = m11;
	this->_m[1][1] = m12;
	this->_m[1][2] = m13;
	this->_m[1][3] = m14;

	this->_m[2][0] = m21;
	this->_m[2][1] = m22;
	this->_m[2][2] = m23;
	this->_m[2][3] = m24;

	this->_m[3][0] = m31;
	this->_m[3][1] = m32;
	this->_m[3][2] = m33;
	this->_m[3][3] = m34;
}

Matrix3D& Matrix3D::operator= (const Matrix3D &rhs)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->_m[i][j] = rhs._m[i][j];
		}
	}

	return *this;

}

const float Matrix3D::GetValues(int x, int y)
{
	return this->_m[x][y];
}

const Matrix3D Matrix3D::operator*(const Matrix3D &other) const
{
	Matrix3D _temp;

	_temp = Matrix3D();

	/*
		Doing the multiplications here.	
	*/

	_temp.SetValues(0,0, ((this->_m[0][0] * other._m[0][0]) + (this->_m[0][1] * other._m[1][0]) + (this->_m[0][2] * other._m[2][0]) + (this->_m[0][3] * this->_m[3][0]))); // 0 - 0
	_temp.SetValues(0,1, ((this->_m[0][0] * other._m[0][1]) + (this->_m[0][1] * other._m[1][1]) + (this->_m[0][2] * other._m[2][1]) + (this->_m[0][3] * this->_m[3][1]))); // 0 - 1
	_temp.SetValues(0,2, ((this->_m[0][0] * other._m[0][2]) + (this->_m[0][1] * other._m[1][2]) + (this->_m[0][2] * other._m[2][2]) + (this->_m[0][3] * this->_m[3][2]))); // 0 - 2
	_temp.SetValues(0,3, ((this->_m[0][0] * other._m[0][3]) + (this->_m[0][1] * other._m[1][3]) + (this->_m[0][2] * other._m[2][3]) + (this->_m[0][3] * this->_m[3][3]))); // 0 - 2

	_temp.SetValues(1,0, ((this->_m[1][0] * other._m[0][0]) + (this->_m[1][1] * other._m[1][0]) + (this->_m[1][2] * other._m[2][0]) + (this->_m[1][3] * this->_m[3][0]))); // 1 - 0
	_temp.SetValues(1,1, ((this->_m[1][0] * other._m[0][1]) + (this->_m[1][1] * other._m[1][1]) + (this->_m[1][2] * other._m[2][1]) + (this->_m[1][3] * this->_m[3][1]))); // 1 - 1
	_temp.SetValues(1,2, ((this->_m[1][0] * other._m[0][2]) + (this->_m[1][1] * other._m[1][2]) + (this->_m[1][2] * other._m[2][2]) + (this->_m[1][3] * this->_m[3][2]))); // 1 - 2
	_temp.SetValues(1,3, ((this->_m[1][0] * other._m[0][3]) + (this->_m[1][1] * other._m[1][3]) + (this->_m[1][2] * other._m[2][3]) + (this->_m[1][3] * this->_m[3][3]))); // 1 - 3

	_temp.SetValues(2,0, ((this->_m[2][0] * other._m[0][0]) + (this->_m[2][1] * other._m[1][0]) + (this->_m[2][2] * other._m[2][0]) + (this->_m[2][3] * this->_m[3][0]))); // 2 - 0
	_temp.SetValues(2,1, ((this->_m[2][0] * other._m[0][1]) + (this->_m[2][1] * other._m[1][1]) + (this->_m[2][2] * other._m[2][1]) + (this->_m[2][3] * this->_m[3][1]))); // 2 - 1
	_temp.SetValues(2,2, ((this->_m[2][0] * other._m[0][2]) + (this->_m[2][1] * other._m[1][2]) + (this->_m[2][2] * other._m[2][2]) + (this->_m[2][3] * this->_m[3][2]))); // 2 - 2
	_temp.SetValues(2,3, ((this->_m[2][0] * other._m[0][3]) + (this->_m[2][1] * other._m[1][3]) + (this->_m[2][2] * other._m[2][3]) + (this->_m[2][3] * this->_m[3][3]))); // 2 - 3

	_temp.SetValues(3,0, ((this->_m[3][0] * other._m[0][1]) + (this->_m[3][1] * other._m[1][0]) + (this->_m[3][2] * other._m[2][0]) + (this->_m[3][3] * this->_m[3][0]))); // 3 - 0
	_temp.SetValues(3,1, ((this->_m[3][0] * other._m[0][1]) + (this->_m[3][1] * other._m[1][1]) + (this->_m[3][2] * other._m[2][1]) + (this->_m[3][3] * this->_m[3][1]))); // 3 - 1
	_temp.SetValues(3,2, ((this->_m[3][0] * other._m[0][2]) + (this->_m[3][1] * other._m[1][2]) + (this->_m[3][2] * other._m[2][2]) + (this->_m[3][3] * this->_m[3][2]))); // 3 - 2
	_temp.SetValues(3,3, ((this->_m[3][0] * other._m[0][2]) + (this->_m[3][1] * other._m[1][3]) + (this->_m[3][2] * other._m[2][3]) + (this->_m[3][3] * this->_m[3][3]))); // 3 - 3


	return _temp;
}

const Vertex Matrix3D::operator*(const Vertex &p) const
{
	/*
		Multiplying a vertex by a matrix
	*/

	// Need to update this

	Vertex temp;

	temp.SetX((this->_m[0][0]  * p.GetX()) + (this->_m[0][1]  * p.GetY()) + (this->_m[0][2] * p.GetZ()) + (this->_m[0][3] * p.GetW()));
	temp.SetY((this->_m[1][0]  * p.GetX()) + (this->_m[1][1]  * p.GetY()) + (this->_m[1][2] * p.GetZ()) + (this->_m[1][3] * p.GetW()));
	temp.SetZ((this->_m[2][0]  * p.GetX()) + (this->_m[2][1]  * p.GetY()) + (this->_m[2][2] * p.GetZ()) + (this->_m[2][3] * p.GetW()));
	temp.SetW((this->_m[3][0]  * p.GetX()) + (this->_m[3][1]  * p.GetY()) + (this->_m[3][2] * p.GetZ()) + (this->_m[3][3] * p.GetW()));

	temp.GetColor().SetValue(p.GetColor().GetValue());

	return temp;

}

void Matrix3D::SetValues(int x, int y, float value)
{
	this->_m[x][y] = value;
}

// Destructor
Matrix3D::~Matrix3D()
{
	// Do nothing for now
}

// Operator overrides

const Matrix3D Matrix3D::MakeRotation(float xRotation, float yRotation, float zRotation)
{
	Matrix3D tempX;
	Matrix3D tempY;
	Matrix3D tempZ;

	Matrix3D temp;

	tempX = Matrix3D(1,0,0,0,
					 0,cos(xRotation),sin(xRotation),0,
					 0,-sin(xRotation),cos(xRotation),0,
					 0,0,0,1);

	tempY = Matrix3D(cos(yRotation),0,-sin(yRotation),0,
					 0,1,0,0,
					 sin(yRotation),0,cos(yRotation),0,
					 0,0,0,1);

	tempZ = Matrix3D(cos(zRotation),sin(zRotation),0,0,
					 -sin(zRotation),cos(zRotation),0,0,
					 0,0,1,0,
					 0,0,0,1);

	temp = tempX * tempY * tempZ;

	return temp;
}

const float Matrix3D::DegreesToRadians(int degrees)
{
	float PI = 3.14f;
	return degrees * PI / 180;
}
