#pragma once
#include "Vertex.h"
#include "Matrix2D.h"
#include "Model3D.h"
#include "Polygon3D.h"
#include "Matrix3D.h"
#include <GdiPlus.h>
#include <string>

using namespace Gdiplus;

struct ScanLine
{
	float xStart;
	float xEnd;

	Gdiplus::Color _scanColor;

	int rStart;
	int gStart;
	int bStart;

	int rEnd;
	int gEnd;
	int bEnd;
};

class Rasterizer
{
	public:
		Rasterizer(unsigned int width, unsigned int height);
		~Rasterizer(void);
		
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		Bitmap * GetBitmap() const;

		void Clear(const Color& color);

		void DrawSquare(Vertex _vert[]);

		void DrawSolidGDIFlat(const Model3D& model);
		void DrawSolidFlat(const Model3D& model);
		void DrawSolidGoraud(const Model3D& model);

		void DrawDemoText(int _demoValue);

		void DrawWireframeBackface(const Model3D& model); // Required for drawing given model
		void DrawWireframe(const Model3D& model);

		void DrawSolidFill(const Model3D& model);

		void InterpolateVerts(Vertex _one, Vertex _two);

		void InterpolateVertsWithColour(Vertex _one, Vertex _two);

		void FillPolygonGoraud(Vertex _one, Vertex _two, Vertex _three);
		void FillPolygon(Vertex _one, Vertex _two, Vertex _three, Gdiplus::Color _color);

	private:
		unsigned int _width;
		unsigned int _height;
		Bitmap * _bitmap;
		Graphics * _graphics; 

		ScanLine* _scanLines;

		//std::vector<ScanLine> _scanLines;

		//ScanLine _scanLines[640];

		// Private constructor. Should not be used directly.
		Rasterizer(void);
};

