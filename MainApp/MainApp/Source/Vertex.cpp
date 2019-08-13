#include "stdafx.h"
#include "Vertex.h"

// Constructors

Vertex::Vertex(void) : _x(0.f), _y(0.f), _z(0.f)
{
	Init(0.0f, 0.0f, 0.0f,0.0f);
}

// Constructor
Vertex::Vertex(float x, float y, float w)
{
	Init(x, y, w, 0.0f);
}

// Constructor
Vertex::Vertex(float x, float y, float z, float w)
{
	Init(x, y, w, z);
}

Vertex::Vertex(const Vertex& v)
{
	Copy(v);
}

Vertex::~Vertex(void)
{
}

void Vertex::SubtractColour(Gdiplus::Color _colorTwo)
{
	Gdiplus::ARGB temp_argb;

	int r,g,b;

	r = (this->_color.GetR() - _colorTwo.GetR());
	g = (this->_color.GetG() - _colorTwo.GetG());
	b = (this->_color.GetB() - _colorTwo.GetB());

	temp_argb = Color::MakeARGB(255, r, g, b);
}

// Accessors and mutators

float Vertex::GetX(void) const
{
	return _x;
}

float Vertex::GetW(void) const
{
	return _w;
}

void Vertex::SetX(float x)
{
	_x = x;
}

float Vertex::GetY(void) const
{
	return _y;
}

void Vertex::SetY(float y)
{
	_y = y;
}

float Vertex::GetZ(void) const
{
	return _z;
}

void Vertex::SetZ(float z)
{
	_z = z;
}

void Vertex::SetW(float w)
{
	_w = w;
}

// More mutators
Vector3D Vertex::GetNormal() const
{
	return this->_normal;
}

Gdiplus::Color Vertex::GetColor() const
{
	return this->_color;
}

void Vertex::BumpNormalContribCount()
{
	this->_useCount++;
}

Vertex Vertex::Zero = Vertex(0.f,0.f,0.f);

const int Vertex::GetNormalContribCount() const
{
	return this->_useCount;
}

void Vertex::SetNormalContribCount(int _newCount)
{
	this->_useCount = _newCount;
}

void Vertex::SetNormal(Vector3D _newNormal)
{
	this->_normal = _newNormal;
}

Vector3D Vertex::Subtract(Vertex other)
{
	Vector3D temp(this->_x - other._x,
				  this->_y - other._y,
				  this->_z - other._z);
	return temp;
}

void Vertex::SetColor(Gdiplus::ARGB _argb)
{
	this->_color.SetValue(_argb);
}

// Operator overloads

Vertex& Vertex::operator= (const Vertex &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

Vertex& Vertex::operator- (const Vertex &rhs)
{
	this->SetW(this->_w - rhs.GetW());
	this->SetX(this->_x - rhs.GetX());
	this->SetY(this->_y - rhs.GetY());

	return *this;
}

// Private methods

void Vertex::Init(float x, float y, float w, float z)
{
	_x = x;
	_y = y;
	_w = w;
	_z = z;

//	this->_normal = Vector3D(0,0,0);
}

void Vertex::Copy(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
	_color = v._color;
}

void Vertex::Dehomogenize()
{
	this->_x = _x / _w;
	this->_y = _y / _w;
	this->_z = _z / _w;
	this->_w = _w / _w; // Squee, slash everything by "w"
}

