#pragma once
#include <GdiPlus.h>
#include "Vector3D.h"

class Polygon3D
{
public:
	Polygon3D(void); // Constructor
	~Polygon3D(void); // Destructor

	Polygon3D(int vertOne, int vertTwo, int vertThree);

	void SetValue(int index, int value);
	int GetValue(int index);

	float GetAverage();
	void SetAverage(float);

	bool GetBackfacing();

	void SetBackfacing(bool);

	Gdiplus::Color GetColor();
	void SetColor(Gdiplus::ARGB _argb);
	
	void SetNormal(Vector3D value);
	const Vector3D GetNormal();

private:
	int vertexIndex[3];
	bool backFacing;
	float averageZ;

	Gdiplus::Color _color;

	byte a;
	byte r;
	byte g;
	byte b;

	//Color _newcolor;
	Vector3D _normal;
};

