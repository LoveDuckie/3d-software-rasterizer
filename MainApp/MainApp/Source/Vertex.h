#pragma once
#include <GdiPlus.h>
#include "Vector3D.h"
#include "Defines.h"

using namespace Gdiplus;

class Vertex
{
	public:
		Vertex();
		Vertex(float x, float y, float w);
		Vertex(float x, float y, float z, float w);
		Vertex(const Vertex& v);
		~Vertex();

		float GetX(void) const;
		void SetX(float);
		
		float GetY(void) const;
		void SetY(float);
		
		float GetW(void) const;
		void SetW(float);
		
		float GetZ(void) const;
		void SetZ(float);

		void SubtractColour(Gdiplus::Color _color);
		void SetColor (Gdiplus::ARGB _argb);
		Gdiplus::Color GetColor() const;
		
		Vector3D GetNormal() const;
		void SetNormal(Vector3D _newNormal);

		Vector3D Subtract(Vertex other);

		// Figure this out later
		void Dehomogenize();

		Vertex& operator= (const Vertex &rhs);
		Vertex& operator- (const Vertex &rhs);

		void SetNormalContribCount(int);
		const int GetNormalContribCount() const;
		void BumpNormalContribCount();

		static Vertex Zero;

	private:
		float _x;
		float _y;
		float _w;
		float _z;

		Gdiplus::Color _color;
		Vector3D _normal;

		int _useCount;
		
		void Init(float x, float y, float w, float z);
		void Copy(const Vertex& v);
};

