#include "stdafx.h"
#include "DirectionalLight.h"

using namespace Gdiplus;

// Default constructor
DirectionalLight::DirectionalLight(void)
{
	this->_position = Vector3D(0,0,0);
	this->_color = Color::Aqua; // For testing
}

DirectionalLight::DirectionalLight(int r, int g, int b)
{
	Gdiplus::ARGB temp_argb;

	temp_argb = Color::MakeARGB(255,r,g,b);

	this->_color = Color(temp_argb);

	this->_position = Vector3D(0,0,0);
}

DirectionalLight::~DirectionalLight(void)
{
	// Destructor
}

// Assign position
DirectionalLight::DirectionalLight(Vector3D _pos)
{
	this->_position = _pos;
	this->_color = Color::Aqua; // For testing
}

Vector3D DirectionalLight::GetPosition()
{
	return this->_position;
}

void DirectionalLight::SetPosition(float x, float y, float z)
{
	this->_position.SetX(x);
	this->_position.SetY(y);
	this->_position.SetZ(z);
}

// Fetch & Set Color Object
Gdiplus::Color DirectionalLight::GetColor() const
{
	return this->_color;
}

void DirectionalLight::SetColor(Gdiplus::ARGB _argb)
{
	this->_color = _argb;
}