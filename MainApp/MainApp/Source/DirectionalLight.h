#pragma once
#include "Vector3D.h"
//#include "Vertex.h"
#include <Windows.h>
#include <GdiPlus.h>

// BYTE added in case Windows.h is not included.
//typedef unsigned char BYTE; 

class DirectionalLight
{
	public:
		DirectionalLight(void);
		DirectionalLight(int,int,int);
		~DirectionalLight(void);

		DirectionalLight(Vector3D _pos);

		Vector3D GetPosition();
		void SetPosition(float, float, float);

		Gdiplus::Color GetColor() const;
		void SetColor(Gdiplus::ARGB _argb);

	private:
		Vector3D _position;

		Gdiplus::Color _color;

		//byte a;
		//byte r;
		//byte g;
		//byte b;
};