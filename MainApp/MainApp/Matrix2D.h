#pragma once
#include "Vertex.h"

class Matrix2D
{
	public:
		Matrix2D(void);
		Matrix2D(float, float, float,
				float, float, float,
				float, float, float);
		Matrix2D(const Matrix2D&);
		~Matrix2D();

		Matrix2D& operator= (const Matrix2D &rhs);
		
		const Matrix2D operator*(const Matrix2D &other) const;
		const Vertex operator*(const Vertex &p) const;
		const Vertex operator+(const Vertex &p) const;

		void SetValues(int x, int y, float value);

		float const GetValues(int x, int y);

	private:

		float _m[3][3];

		void Init(float, float, float,
				  float, float, float,
				  float, float, float);

		void Copy(const Matrix2D& m);
};

