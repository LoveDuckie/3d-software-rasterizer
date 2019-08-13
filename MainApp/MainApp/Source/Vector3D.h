#pragma once
// A unit vector is a vector that has a length of 1

// Made for calculating the distance and length from different vectors.
// NOT A POINT IN SPACE D:<

// x means displacement in the X direction, not the position. Similar for the other y & z properties.

#include <math.h>


class Vector3D
{
public:
	Vector3D(void);
	Vector3D(const Vector3D& rhs);
	Vector3D(float, float, float);
	~Vector3D(void);
	
	const float& GetX() const;
	const float& GetY() const;
	const float& GetZ() const;

	void SetX(float);
	void SetY(float);
	void SetZ(float);

	float Magnitude();
	Vector3D Normalise();

	void DivideByInt(int);

	static void StatNormalise(Vector3D _vector);

	const Vector3D operator+ (const Vector3D &other);
	const Vector3D operator- (const Vector3D &other);

	//Vector3D& operator= (const Vector3D &other);

	//void SubstractVertices(Vertex other_one, Vertex other_two);
	
	// Dot Product, Cross Product, implement later.

	float DotProduct(const Vector3D &other);
	Vector3D CrossProduct(const Vector3D &other);

	const float& GetLength() const;

private:
	float _x;
	float _y;
	float _z;

	float _length; // Magnitude
};