#pragma once

#include <math.h>

class Matrix3D
{
	public:
		Matrix3D(void);
		Matrix3D(float, float, float, float,
				float, float, float, float,
				float, float, float, float,
				float, float, float, float);

		Matrix3D(const Matrix3D&);
		~Matrix3D();

		Matrix3D& operator= (const Matrix3D &rhs);
		
		const Matrix3D operator*(const Matrix3D &other) const;
		const Vertex operator*(const Vertex &p) const;
		const Vertex operator+(const Vertex &p) const;

		void SetValues(int x, int y, float value);

		const static Matrix3D MakeRotation(float, float, float);

		const float GetValues(int x, int y);

		const float static DegreesToRadians(int degrees);

	private:

		float _m[4][4];

		void Init(float, float, float, float,
				  float, float, float, float,
				  float, float, float, float,
				  float, float, float, float);

		void Copy(const Matrix3D& m);
};