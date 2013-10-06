#include "StdAfx.h"
#include "Rasterizer.h"
#include "Vertex.h"
#include <GdiPlus.h>
#include <string>

Rasterizer::Rasterizer(void)
{
	// Declared private so should not be called.
	_bitmap = NULL;
	_graphics = NULL;

	this->_height = 640;
	this->_width = 480;

	_scanLines = new ScanLine[_height];
}

Rasterizer::Rasterizer(unsigned int width, unsigned int height)
{
	// Create a bitmap of the specified size and get a reference to the graphics object
	// for that bitmap. Note that these calls could theoretically fail so we really should
	// handle that, but we will leave that for now. 
	_width = width;
	_height = height;
	_bitmap = new Bitmap(_width, _height, PixelFormat32bppARGB);
	_graphics = new Graphics(_bitmap);

	_scanLines = new ScanLine[_height];
}

void Rasterizer::DrawDemoText(int _demoValue)
{
	WCHAR _wireFrame[] = L"Basic wireframe";
	WCHAR _backFace[] = L"Basic wireframe with back-face culling";
	WCHAR _fillPolygon[] = L"Filled polygon";
	WCHAR _flatShading[] = L"Flat-shading (GDI+)";
	WCHAR _flatShadingInt[] = L"Flat-shading (Interpolation)";
	WCHAR _MyName[] = L"3D Software Renderer - Luc Shelton - 100119601";

	RectF nameRect(0.0f, 15.0f, 400.0f, 50.0f);
	RectF layoutRect(0.0f, 50.0f, 400.0f, 50.0f);
	Font myFont(L"Tahoma", 12);
	
	StringFormat _format;

	_format.SetAlignment(StringAlignmentCenter);

	SolidBrush _blackBrush(Color::Black);
	
	// Write my name on the screen
			_graphics->DrawString(
			_MyName,
			wcslen(_MyName),
			&myFont,
			nameRect,
			&_format,
			&_blackBrush);

			// Varying on what demo screen has been selected will display different text.
	switch(_demoValue)
	{
		// Wireframe
	case 1:
		_graphics->DrawString(
			_wireFrame,
			wcslen(_wireFrame),
			&myFont,
			layoutRect,
			&_format,
			&_blackBrush);

		break;

		// Backface Culling
	case 2:
			_graphics->DrawString(
			_backFace,
			wcslen(_backFace),
			&myFont,
			layoutRect,
			&_format,
			&_blackBrush);

		break;

		// FillPolygon
	case 3:
			_graphics->DrawString(
			_fillPolygon,
			wcslen(_fillPolygon),
			&myFont,
			layoutRect,
			&_format,
			&_blackBrush);

		break;

		// Flat Shading
	case 4:
			_graphics->DrawString(
			_flatShading,
			wcslen(_flatShading),
			&myFont,
			layoutRect,
			&_format,
			&_blackBrush);

		break;

	case 5:
			_graphics->DrawString(
			_flatShadingInt,
			wcslen(_flatShadingInt),
			&myFont,
			layoutRect,
			&_format,
			&_blackBrush);
		break;
	}

	// Do draw text stuff here.
}

Rasterizer::~Rasterizer(void)
{
	// Clean up all dynamically created objects
	if (_graphics)
	{
		delete _graphics;
		_graphics = NULL;
	}
	if (_bitmap)
	{
		delete _bitmap;
		_bitmap = NULL;
	}

	if (_scanLines)
	{
		delete [] _scanLines;
		_scanLines = NULL;
	}
}

// Accessors

unsigned int Rasterizer::GetWidth() const
{
	return _width;
}

unsigned int Rasterizer::GetHeight() const
{
	return _height;
}

Bitmap * Rasterizer::GetBitmap() const
{
	return _bitmap;
}

// Clear the bitmap using the specified colour

void Rasterizer::Clear(const Color& color)
{
	if (_graphics)
	{
		_graphics->Clear(color);
	}
}

// Interpolation faceted shading
void Rasterizer::DrawSolidFlat(const Model3D& model)
{
	Model3D tempMod = model;

	Vertex _tempVertOne, _tempVertTwo, _tempVertThree;
	Polygon3D _tempPoly;

	for (int i = 0; i < (int) tempMod.GetPolygons().size(); i++)
	{
		_tempPoly = tempMod.GetPolygon(i);

		if (_tempPoly.GetBackfacing())
		{
		_tempVertOne = tempMod.GetTransformedVertex(_tempPoly.GetValue(0));
		_tempVertTwo = tempMod.GetTransformedVertex(_tempPoly.GetValue(1));
		_tempVertThree = tempMod.GetTransformedVertex(_tempPoly.GetValue(2));

		this->FillPolygon(_tempVertOne,_tempVertTwo,_tempVertThree, _tempPoly.GetColor());
		}
	}
}

// No shading - polygon fill.
void Rasterizer::DrawSolidFill(const Model3D& model)
{
	Model3D tempMod = model;
	Vertex _tempVertOne, _tempVertTwo, _tempVertThree;
	Polygon3D _tempPoly;
	Gdiplus::Color _color(Color::Aqua);

	SolidBrush _brush(_color);

	PointF point1,point2,point3;

	PointF _verts[3];

	PointF* pPoints = _verts;

	for (int i = 0; i < (int) tempMod.GetPolygons().size(); i++)
	{
		_tempPoly = tempMod.GetPolygon(i);

		_tempVertOne = tempMod.GetTransformedVertex(_tempPoly.GetValue(0));
		_tempVertTwo = tempMod.GetTransformedVertex(_tempPoly.GetValue(1));
		_tempVertThree = tempMod.GetTransformedVertex(_tempPoly.GetValue(2));

		point1 = PointF(_tempVertOne.GetX(),_tempVertOne.GetY());
		point2 = PointF(_tempVertTwo.GetX(),_tempVertTwo.GetY());
		point3 = PointF(_tempVertThree.GetX(),_tempVertThree.GetY());

		_verts[0] = point1;
		_verts[1] = point2;
		_verts[2] = point3;

		_graphics->FillPolygon(&_brush,pPoints,3);
	}
}

// Interpolation for discovering the edges and filling the middle.
void Rasterizer::InterpolateVerts(Vertex _one, Vertex _two)
{
	if (_two.GetY() < _one.GetY())
	{
		Vertex _three = _two;
		_two = _one;
		_one = _three;
	}

	// How many points that the scan goes through
	float _yDifference = (_two.GetY() - _one.GetY()); // Store differences here, saves having to call the mutator method continously.
	float _xDifference = (_two.GetX() - _one.GetX());
	
	float _numPoints = _two.GetY() - _one.GetY();

	// To prevent mutators getting called repetitively
	float _oneX = _one.GetX();
	float _oneY = _one.GetY();

	// Loop through for the amount of lines that are between the two Y verts.
	for (int i = 0; i < _numPoints; i++)
	{
		int scanline = (int) _oneY + i;

		if (scanline < 0 || scanline >= (int) _height)
			continue;

		float x = _oneX + i * (_xDifference / _yDifference); // Finding the gradient..

		/*
			By default the _scanLine[] should be defaulted to xStart = 640 and xEnd = 0
		*/

		if (x < _scanLines[scanline].xStart)
				_scanLines[scanline].xStart = x;

		if (x > _scanLines[scanline].xEnd)
				_scanLines[scanline].xEnd = x;
	}

}

void Rasterizer::DrawSolidGoraud(const Model3D &model)
{
	
	Model3D tempMod;
	tempMod = model;

	Polygon3D tempPoly;
	Vertex _one, _two, _three;

	// Test vertices for ascertaining that I can produce a gradient.
	Vertex _tOne, _tTwo, _tThree;

	Gdiplus::ARGB vOne, vTwo, vThree;

	// Producing temporary colours
	vOne = Color::MakeARGB(255,0,255,0);
	vTwo = Color::MakeARGB(255,0,0,255);
	vThree = Color::MakeARGB(255,255,0,0);

	_tOne.SetX(200.0f);
	_tOne.SetY(200.0f);

	_tTwo.SetX(300.0f);
	_tTwo.SetY(300.0f);

	_tThree.SetX(200.0f);
	_tThree.SetY(300.0f);

	_tOne.SetColor(vOne);
	_tTwo.SetColor(vTwo);
	_tThree.SetColor(vThree);

	for (int i = 0; i < (int) tempMod.GetPolygons().size();i++)
	{
		tempPoly = tempMod.GetPolygon(i);

		_one = tempMod.GetTransformedVertex(tempPoly.GetValue(0));
		_two = tempMod.GetTransformedVertex(tempPoly.GetValue(1));
		_three = tempMod.GetTransformedVertex(tempPoly.GetValue(2));
		
		FillPolygonGoraud(_one,_two,_three);
	}

	// Use the fake vertices that i've generated
	//FillPolygonGoraud(_tOne,_tTwo,_tThree);
}

void Rasterizer::FillPolygonGoraud(Vertex _one, Vertex _two, Vertex _three)
{
	for (int i = 0; i < (int) _height; i++)
	{
		_scanLines[i].xStart = (float) _width;
		_scanLines[i].xEnd = 0.0f;
		_scanLines[i].rStart = 255;
		_scanLines[i].gStart = 255;
		_scanLines[i].bStart = 255;
		_scanLines[i].rEnd = 0;
		_scanLines[i].gEnd = 0;
		_scanLines[i].bEnd = 0;
	}

	int ScanLineMax = 0;
	int ScanLineMin = 0;

		// Vertex One compared to scanlinemax
	if ((int) _one.GetY() > ScanLineMax)
		ScanLineMax = (int) _one.GetY();
	else if ((int) _one.GetY() < ScanLineMin)
		ScanLineMin = (int) _one.GetY();

	// Vertex Two compared to scanlinemax
	if ((int) _two.GetY() > ScanLineMax)
		ScanLineMax = (int) _two.GetY();
	else if ((int)_two.GetY() < ScanLineMin)
		ScanLineMin = (int) _two.GetY();

	// Vertex Three compared to scanlinemax
	if ((int) _three.GetY() > ScanLineMax)
		ScanLineMax = (int) _three.GetY();
	else if ((int) _three.GetY() < ScanLineMin)
		ScanLineMin = (int) _three.GetY();

	InterpolateVertsWithColour(_one,_two);
	InterpolateVertsWithColour(_two,_three);
	InterpolateVertsWithColour(_three,_one);

	// Actual calculation of the gradient
	int tempR, tempG, tempB;

	// To be called into set pixel.
	Gdiplus::ARGB temp_argb;

	// Adding the gradient somewhere
	

	for (int y = 0; y < (int) _height; y++)
	{
		int currentR = 0, currentG = 0, currentB = 0;

		currentR = _scanLines[y].rStart;
		currentG = _scanLines[y].gStart;
		currentB = _scanLines[y].bStart;

		for (int x = (int) _scanLines[y].xStart; x <= (int) _scanLines[y].xEnd; x++) // Keep looping through the difference between the xStart and xEnd
		{
			tempR = (int) ((_scanLines[y].rStart - _scanLines[y].rEnd) / (_scanLines[y].xStart - _scanLines[y].xEnd));  
			tempG = (int) ((_scanLines[y].gStart - _scanLines[y].gEnd) / (_scanLines[y].xStart - _scanLines[y].xEnd));
			tempB = (int) ((_scanLines[y].bStart - _scanLines[y].bEnd) / (_scanLines[y].xStart - _scanLines[y].xEnd));  

			temp_argb = Color::MakeARGB(255,currentR,currentG,currentB);

			currentR += tempR;
			currentG += tempG;
			currentB += tempB;

			_bitmap->SetPixel(x,y,Color(temp_argb));
		}
	}

}

void Rasterizer::InterpolateVertsWithColour(Vertex _one, Vertex _two)
{
	// Gradient
	int temp_r,temp_g,temp_b;
	
	// Which one is higher or lower?
	if (_two.GetY() < _one.GetY())
	{
		Vertex _three = _two;
		_two = _one;
		_one = _three;
	}
	
	int v1_r, v1_g, v1_b;
	int v2_r, v2_g, v2_b; 

	// Used for the gradient
	float _yDifference = (_two.GetY() - _one.GetY()); // Store differences here, saves having to call the mutator method continously.
	float _xDifference = (_two.GetX() - _one.GetX());

	// How many points are there between the two verts in height.
	float _numPoints = _two.GetY() - _one.GetY();

	v1_r = _one.GetColor().GetR();
	v1_g = _one.GetColor().GetG();
	v1_b = _one.GetColor().GetB();

	v2_r = _two.GetColor().GetR();
	v2_g = _two.GetColor().GetG();
	v2_b = _two.GetColor().GetB();

	// Temp vars being the gradient for the colour, calculated 
	temp_r = (int) ((v2_r - v1_r) / _numPoints);
	temp_g = (int) ((v2_g - v1_g) / _numPoints);
	temp_b = (int) ((v2_g - v1_b) / _numPoints);

	// These are the values that the gradient will be applied to.
	int currentR = 0, currentG = 0, currentB = 0;


	// Gradient incremental colours
	currentR = v1_r;
	currentG = v1_g;
	currentB = v1_b;

	// To prevent mutators getting called repetitively
	float _oneX = _one.GetX();
	float _oneY = _one.GetY();

	// Loop through for the amount of lines that are between the two Y verts.
	for (int i = 0; i < _numPoints; i++)
	{
		// Scanline positions itself at the given Y value plus the i value of the loop
		int scanline = (int) _oneY + i;

		if (scanline < 0 || scanline >= (int) _height)
			continue;

		float x = _oneX + i * (_xDifference / _yDifference); // Finding the gradient..

		//By default the _scanLine[] should be defaulted to xStart = 640 and xEnd = 0
		// So these conditions should always come out true on the first loop through.
		

		// If the scanline is greater than the defaulted sizes, then replace.
		if (x < _scanLines[scanline].xStart)
		{
			_scanLines[scanline].xStart = x;
			_scanLines[scanline].rStart = (currentR > 255 ? 255 : (currentR < 0 ? 0 : currentR));
			_scanLines[scanline].gStart = (currentG > 255 ? 255 : (currentG < 0 ? 0 : currentG));
			_scanLines[scanline].bStart = (currentB > 255 ? 255 : (currentB < 0 ? 0 : currentB));
		}

		if (x > _scanLines[scanline].xEnd)
		{
			_scanLines[scanline].xEnd = x;
			_scanLines[scanline].rEnd = (currentR > 255 ? 255 : (currentR < 0 ? 0 : currentR));
			_scanLines[scanline].gEnd = (currentG > 255 ? 255 : (currentG < 0 ? 0 : currentG));
			_scanLines[scanline].bEnd = (currentB > 255 ? 255 : (currentB < 0 ? 0 : currentB));
		}

		
		currentR += temp_r;
		currentG += temp_g;
		currentB += temp_b;
	}
}

void Rasterizer::FillPolygon(Vertex _one, Vertex _two, Vertex _three, Gdiplus::Color _color)
{
	// Setting the default scan values to width.
	for (int i = 0; i < (int) _height; i++)
	{
		_scanLines[i].xStart = (float) _width;
		_scanLines[i].xEnd = 0.0f;
	}

	int ScanLineMax = 0;
	int ScanLineMin = 0;

	// Determining the max and min loop points for the scanlines array
	// So that when we perform the final loop at the bottom, the iteration doesn't take as long

	// Vertex One compared to scanlinemax
	if ((int) _one.GetY() > ScanLineMax)
		ScanLineMax = (int) _one.GetY();
	else if ((int) _one.GetY() < ScanLineMin)
		ScanLineMin = (int) _one.GetY();

	// Vertex Two compared to scanlinemax
	if ((int) _two.GetY() > ScanLineMax)
		ScanLineMax = (int) _two.GetY();
	else if ((int)_two.GetY() < ScanLineMin)
		ScanLineMin = (int) _two.GetY();

	// Vertex Three compared to scanlinemax
	if ((int) _three.GetY() > ScanLineMax)
		ScanLineMax = (int) _three.GetY();
	else if ((int) _three.GetY() < ScanLineMin)
		ScanLineMin = (int) _three.GetY();

	// Find the edges of the vert with interpolation
	InterpolateVerts(_one,_two);
	InterpolateVerts(_two,_three);
	InterpolateVerts(_three,_one);

	// Find the difference between xStart & xEnd and draw between those
	for (int y = 0; y < (int) _height; y++)
	{
		for (int x = (int) _scanLines[y].xStart; x <= (int) _scanLines[y].xEnd; x++) // Keep looping through the difference between the xStart and xEnd
		{
			_bitmap->SetPixel(x,y,_color);
		}
	}
}

void Rasterizer::DrawSolidGDIFlat(const Model3D& model)
{
	// Loading up the temporary variables
	//SolidBrush _brush(Color::Blue);

	Model3D tempMod = model;

	PointF point1,point2,point3;

	Vertex _vert1, _vert2, _vert3;
	Polygon3D tempPoly;

	PointF _verts[3];

	PointF* pPoints = _verts;

	// Crappy loop to get all the data in and then .. yeah w00t.
	for (int i = 0; i < (int) tempMod.GetPolygons().size(); i++)
	{
		tempPoly = tempMod.GetPolygon(i);


		if (tempPoly.GetBackfacing())
		{
		// Loading in the verts
		_vert1 = tempMod.GetTransformedVertex(tempPoly.GetValue(0));
		_vert2 = tempMod.GetTransformedVertex(tempPoly.GetValue(1));
		_vert3 = tempMod.GetTransformedVertex(tempPoly.GetValue(2));
		
		// Setting up the verts positions
		point1 = PointF(_vert1.GetX(),_vert1.GetY());
		point2 = PointF(_vert2.GetX(),_vert2.GetY());
		point3 = PointF(_vert3.GetX(),_vert3.GetY());

		// An array for PointFloats
		_verts[0] = point1;
		_verts[1] = point2;
		_verts[2] = point3;

		SolidBrush _newbrush(tempMod.GetPolygons()[i].GetColor());
		_graphics->FillPolygon(&_newbrush,pPoints,3);
		}
	}

}

// Delicious draw wireframe method :3
void Rasterizer::DrawWireframeBackface(const Model3D& model)
{
	Model3D tempMod = model;
	Pen		pen(Color::Purple);

	for (int i = 0; i < (int) tempMod.GetPolygons().size(); i++)
	{
		// Create a new tempPoly after every
		Polygon3D tempPoly = tempMod.GetPolygon(i);
		
		// If the polygon isn't facing the back don't draw it!
		if (tempPoly.GetBackfacing()) 
		{

			// Polygon obviously has three different points
			Vertex vertA = tempMod.GetTransformedVertex(tempPoly.GetValue(0));
			Vertex vertB = tempMod.GetTransformedVertex(tempPoly.GetValue(1));
			Vertex vertC = tempMod.GetTransformedVertex(tempPoly.GetValue(2));		

			_graphics->DrawLine(&pen,Point((int) vertA.GetX(),(int) vertA.GetY()),Point((int) vertB.GetX(),(int) vertB.GetY()));
			_graphics->DrawLine(&pen,Point((int) vertB.GetX(),(int) vertB.GetY()),Point((int) vertC.GetX(),(int) vertC.GetY()));
			_graphics->DrawLine(&pen,Point((int) vertC.GetX(),(int) vertC.GetY()),Point((int) vertA.GetX(),(int) vertA.GetY()));
		
		}
	}

}

void Rasterizer::DrawWireframe(const Model3D& model)
{
	Model3D tempMod = model;
	Pen		pen(Color::Purple);

	for (int i = 0; i < (int) tempMod.GetPolygons().size(); i++)
	{
		// Create a new tempPoly after every
		Polygon3D tempPoly = tempMod.GetPolygon(i);
		
		// If the polygon isn't facing the back don't draw it!


			// Polygon obviously has three different points
			Vertex vertOne = tempMod.GetTransformedVertex(tempPoly.GetValue(0));
			Vertex vertTwo = tempMod.GetTransformedVertex(tempPoly.GetValue(1));
			Vertex vertThree = tempMod.GetTransformedVertex(tempPoly.GetValue(2));		

			// Draw up the wireframe with our newly transformed vertices.
			_graphics->DrawLine(&pen,Point((int) vertOne.GetX(),(int) vertOne.GetY()),Point((int) vertTwo.GetX(),(int) vertTwo.GetY()));
			_graphics->DrawLine(&pen,Point((int) vertTwo.GetX(),(int) vertTwo.GetY()),Point((int) vertThree.GetX(),(int) vertThree.GetY()));
			_graphics->DrawLine(&pen,Point((int) vertThree.GetX(),(int) vertThree.GetY()),Point((int) vertOne.GetX(),(int) vertOne.GetY()));

	}

}

// Basic 2D drawing
void Rasterizer::DrawSquare(Vertex _vert[])
{
	Pen		pen(Color::Red);
	_graphics->DrawLine(&pen,_vert[0].GetX() ,_vert[0].GetY(), _vert[1].GetX(), _vert[1].GetY());
	_graphics->DrawLine(&pen,_vert[1].GetX() ,_vert[1].GetY(), _vert[2].GetX(), _vert[2].GetY());
	_graphics->DrawLine(&pen,_vert[2].GetX() ,_vert[2].GetY(), _vert[3].GetX(), _vert[3].GetY());
	_graphics->DrawLine(&pen,_vert[3].GetX() ,_vert[3].GetY(), _vert[0].GetX(), _vert[0].GetY());
}


