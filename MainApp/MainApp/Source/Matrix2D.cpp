#include "stdafx.h"
#include "Matrix2D.h"

// Constructors
Matrix2D::Matrix2D(void)
{
	// Declare default initialisation
	//Init(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);

	// Setting default values
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; i++)
		{
			_m[i][j] = 0.0f;
		}
	}

}

Matrix2D::Matrix2D(float m01, float m02, float m03,
				   float m11, float m12, float m13,
				   float m21, float m22, float m23)
{
	Init(m01,m02,m03,m11,m12,13,m21,m22,m23);
}

Matrix2D::Matrix2D(const Matrix2D& m)
{
	Copy(m);
}

void Matrix2D::Copy(const Matrix2D& m)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->_m[i][j] = m._m[i][j];
		}
	}

}

//const Vertex Matrix2D::operator+(const Vertex &p) const
//{
//
//
//
//}

// Initliasation method
void Matrix2D::Init(float m01, float m02, float m03, float m11, float m12, float m13, float m21, float m22, float m23)
{
	this->_m[0][0] = m01;
	this->_m[0][1] = m02;
	this->_m[0][2] = m03;

	this->_m[1][0] = m11;
	this->_m[1][1] = m12;
	this->_m[1][2] = m13;

	this->_m[2][0] = m21;
	this->_m[2][1] = m22;
	this->_m[2][2] = m23;
}

Matrix2D& Matrix2D::operator= (const Matrix2D &rhs)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->_m[i][j] = rhs._m[i][j];
		}
	}

	return *this;

}

float const Matrix2D::GetValues(int x, int y)
{
	return this->_m[x][y];
}

const Matrix2D Matrix2D::operator*(const Matrix2D &other) const
{
	Matrix2D _temp;

	_temp = Matrix2D();

	/*
		Doing the multiplications here.	
	*/

	_temp.SetValues(0,0, (this->_m[0][0] * other._m[0][0]) + (this->_m[0][1] * other._m[1][0]) + (this->_m[0][2] * other._m[2][0])); // 0 - 0
	_temp.SetValues(0,1, (this->_m[0][0] * other._m[0][1]) + (this->_m[0][1] * other._m[1][1]) + (this->_m[0][2] * other._m[2][1])); // 0 - 1
	_temp.SetValues(0,2, (this->_m[0][0] * other._m[0][2]) + (this->_m[0][1] * other._m[1][2]) + (this->_m[0][2] * other._m[2][2])); // 0 - 2

	_temp.SetValues(1,0, (this->_m[1][0] * other._m[0][0]) + (this->_m[1][1] * other._m[1][0]) + (this->_m[1][2] * other._m[2][0])); // 1 - 0
	_temp.SetValues(1,1, (this->_m[1][0] * other._m[0][1]) + (this->_m[1][1] * other._m[1][1]) + (this->_m[1][2] * other._m[2][1])); // 1 - 1
	_temp.SetValues(1,2, (this->_m[1][0] * other._m[0][2]) + (this->_m[1][1] * other._m[1][2]) + (this->_m[1][2] * other._m[2][2])); // 1 - 2

	_temp.SetValues(2,0, (this->_m[2][0] * other._m[0][1]) + (this->_m[2][1] * other._m[1][0]) + (this->_m[2][2] * other._m[2][0])); // 2 - 0
	_temp.SetValues(2,1, (this->_m[2][0] * other._m[0][1]) + (this->_m[2][1] * other._m[1][1]) + (this->_m[2][2] * other._m[2][1])); // 2 - 1
	_temp.SetValues(2,2, (this->_m[2][0] * other._m[0][2]) + (this->_m[2][1] * other._m[1][2]) + (this->_m[2][2] * other._m[2][2])); // 2 - 2

	return _temp;
}

const Vertex Matrix2D::operator*(const Vertex &p) const
{
	/*
		Multiplying a vertex by a matrix
	*/

	Vertex temp;

	temp.SetX((this->_m[0][0]  * p.GetX()) + (this->_m[0][1]  * p.GetY()) + (this->_m[0][2] * 1));
	temp.SetY((this->_m[1][0]  * p.GetX()) + (this->_m[1][1]  * p.GetY()) + (this->_m[1][2] * 1));

	return temp;

}

void Matrix2D::SetValues(int x, int y, float value)
{
	this->_m[x][y] = value;
}

// Destructor
Matrix2D::~Matrix2D()
{
	// Do nothing for now
}

// Operator overrides