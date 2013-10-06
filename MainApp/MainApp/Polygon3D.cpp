#include "stdafx.h"
#include "Vertex.h"
#include "Matrix3D.h"
#include "Polygon3D.h"

Polygon3D::Polygon3D(void)
{
	for (int i = 3; i < 3; i++)
	{
		this->vertexIndex[i] = 0;
	}

	this->backFacing = false;
	this->_color = Gdiplus::Color(255,0,0,0);
}

Polygon3D::~Polygon3D(void)
{
	// Do nothing for noaw.
}

float Polygon3D::GetAverage()
{
	return this->averageZ;
}

void Polygon3D::SetAverage(float value)
{
	this->averageZ = value;
}

Polygon3D::Polygon3D(int vertOne, int vertTwo, int vertThree)
{
	this->vertexIndex[0] = vertOne;
	this->vertexIndex[1] = vertTwo;
	this->vertexIndex[2] = vertThree;

	this->backFacing = false;
}

void Polygon3D::SetValue(int index, int value)
{
	this->vertexIndex[index] = value;
}

int Polygon3D::GetValue(int index)
{
	return this->vertexIndex[index];
}

Gdiplus::Color Polygon3D::GetColor()
{
	return this->_color;
}

void Polygon3D::SetColor(Gdiplus::ARGB _argb)
{
	this->_color = _argb;
}

// Return the backfacing member
bool Polygon3D::GetBackfacing()
{
	return this->backFacing;
}

void Polygon3D::SetBackfacing(bool value)
{
	this->backFacing = value;
}

// Normal Mutators

void Polygon3D::SetNormal(Vector3D value)
{
	this->_normal = value;
}

const Vector3D Polygon3D::GetNormal()
{
	return this->_normal;
}
