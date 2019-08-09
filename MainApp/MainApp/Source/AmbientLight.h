#pragma once
#include <Windows.h>
#include <GdiPlus.h>

using namespace Gdiplus;

class AmbientLight
{
	public:
		AmbientLight(void);
		AmbientLight(int, int, int);
		~AmbientLight(void);

		Gdiplus::Color GetColor() const;
		void SetColor(Gdiplus::ARGB _argb);

	private:
		Color _color;

};