#pragma once
// A unit vector is a vector that has a length of 1

// Made for calculating the distance and length from different vectors.
// NOT A POINT IN SPACE D:<

// x means displacement in the X direction, not the position. Similar for the other y & z properties.

#include <math.h>
#include "Defines.h"
#include <xmmintrin.h>
#include <emmintrin.h>

class Vector3D
{
public:
	Vector3D();
	Vector3D(const Vector3D& rhs);
	Vector3D(float32 x, float32 y, float32 z);
	~Vector3D(void);
	
	const float& GetX() const;
	const float& GetY() const;
	const float& GetZ() const;

	void SetX(float);
	void SetY(float);
	void SetZ(float);

	float32 Magnitude();
	Vector3D Normalise();

	void DivideByInt(int);

	const Vector3D operator+ (const Vector3D& other);
	const Vector3D operator- (const Vector3D& other);
	const Vector3D operator/ (const Vector3D& other);
	const Vector3D operator+ (const int32& other);
	const Vector3D operator/ (const int32& other);

	//Vector3D& operator= (const Vector3D &other);

	//void SubstractVertices(Vertex other_one, Vertex other_two);
	
	// Dot Product, Cross Product, implement later.

	float DotProduct(const Vector3D &other);
	Vector3D CrossProduct(const Vector3D &other);

	// Calculate and retrieve the length from the vector
	const float& GetLength() const;

private:
	float _x;
	float _y;
	float _z;
	__m128 _data;

	float _length; // Magnitude
};