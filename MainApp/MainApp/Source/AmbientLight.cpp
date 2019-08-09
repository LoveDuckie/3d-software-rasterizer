#include "stdafx.h"
#include "AmbientLight.h"

AmbientLight::AmbientLight(void)
{
	this->_color = Color::Yellow;
}

AmbientLight::~AmbientLight(void)
{
	
}

AmbientLight::AmbientLight(int r, int g, int b)
{
	Gdiplus::ARGB temp_argb;

	temp_argb = Color::MakeARGB(255,r,g,b);

	this->_color = Color(temp_argb);
}

void AmbientLight::SetColor(Gdiplus::ARGB _argb)
{
	this->_color = Gdiplus::Color(_argb);
}

Gdiplus::Color AmbientLight::GetColor() const
{
	return this->_color;
}