#include "StdAfx.h"
#include "AppEngine.h"
#include "MD2Loader.h"
#include <cmath>

// Main 'engine' class for our application. This is where all of the core processing work is done

// Small definition for the usage of DELICIOUS PI
static const float PI = 3.14159265f;

bool _demoMode;

using namespace std;
using namespace Framework;

float XRotation = 0.0f;
float YRotation = 0.0174f;
float ZRotation = 0.0f;
int rotationAmount = 0;

bool bXaxis, bYaxis, bZaxis;
int x_axis, y_axis, z_axis;

int _speed;

int _modeIndex = 1;
int _demoTicker;

AppEngine::AppEngine(void)
{
	_rasterizer = NULL;
}

AppEngine::~AppEngine(void)
{
	// Make sure everything is cleaned up (in case Shutdown() was now called directly)
	Shutdown();
}

void AppEngine::ChangeSpeed(int _newspeed)
{
	_speed = _newspeed;
}

void AppEngine::ChangeRotation(std::string _type)
{
	if (_type == "x_axis")
	{
		if (bXaxis == true)
		{
			bXaxis = false;
		}
		else
		{
			bXaxis = true;
		}
	}

	if (_type == "y_axis")
	{
		if (bYaxis == true)
		{
			bYaxis = false;
		}
		else
		{
			bYaxis = true;
		}
	}


	if (_type == "z_axis")
	{
		if (bZaxis == true)
		{
			bZaxis = false;
		}
		else
		{
			bZaxis = true;
		}
	}

}

/* */
void AppEngine::Initialise(HWND hWnd)
{
	_hWnd = hWnd;
	
	Vertex _camVert;

	_speed = 1;


	_demoMode = true;

	x_axis = 0;
	y_axis = 0;
	z_axis = 0;

	bXaxis = true;
	bYaxis = true;
	bZaxis = true;

	_camVert.SetX(-50);
	_camVert.SetY(0);
	_camVert.SetZ(-100);
	_camVert.SetW(1);

	this->_ambientLight = AmbientLight();

	// Add a new light to the list - default position
	this->_directionalLights.push_back(DirectionalLight(Vector3D(2,0,0)));

	this->_camera = Camera(
		           0.0f, 0.0f, 0.0f, // Rotation
				   _camVert, // Position
				   640, // Width
				   480); // Height

	MD2Loader::LoadModel("Cartman.md2",_model);

	// Get the width and height of the window so that we can tell the rasterizer to create a bitmap
	// of the same size.  Note that this only works for the initial size of the window. If you want 
	// your code to handle resizing of the window, you will need to add code for this yourself. 
	LONG width;
	LONG height;
	RECT clientWindowRect;
	if (GetClientRect(_hWnd, &clientWindowRect))
	{
		width = clientWindowRect.right;
		height = clientWindowRect.bottom;
	}
	else
	{
		width = 640;
		height = 480;
	}
	_rasterizer = new Rasterizer((unsigned int)width, (unsigned int)height);


	this->_model.SetKdComponent(0,0.5f);
	this->_model.SetKdComponent(1,0.5f);
	this->_model.SetKdComponent(2,0.5f);

	this->_model.SetKaComponent(0,0.7f);
	this->_model.SetKaComponent(1,0.7f);
	this->_model.SetKaComponent(2,0.7f);

}

void AppEngine::Process(void)
{
	// At the moment, all we do is render a new image. In the future, we might do more here
	Render();
}

void AppEngine::SetAmbientLight(AmbientLight ambLight)
{
	this->_ambientLight = ambLight;
}

const AmbientLight AppEngine::GetAmbientLight()
{
	return this->_ambientLight;
}

void AppEngine::Render(void)
{
	_rasterizer->Clear(Color::LightGray);

	//this->_amblight = AmbientLight(); // Set to default object

		//Matrix3D rotateY(cos(YRotation), 0, sin(YRotation), 0,
		//				 0, 1, 0, 0,
		//				 -sin(YRotation), 0, cos(YRotation), 0,
		//				 0, 0, 0, 1);
	
	this->_model.ApplyTransformToLocalVertices(Matrix3D::MakeRotation(Matrix3D::DegreesToRadians(x_axis),
											   Matrix3D::DegreesToRadians(y_axis),
											   Matrix3D::DegreesToRadians(z_axis)));
	//Vertex _vertex[4] = {Vertex(200.0f,200.0f,0.0f),
	//					 Vertex(250.0f,200.0f,0.0f),
	//					 Vertex(250.0f,250.0f,0.0f),
	//					 Vertex(200.0f,250.0f,0.0f)};
	

	//Matrix2D transform(1.0f,0.0f,5.0f,
	//				   0.0f,1.0f,5.0f,
	//				   0.0f,0.0f,5.0f);

	//Matrix2D scale(0.0f,0.0f,0.0f,
	//			   0.0f,0.0f,0.0f,
	//			   0.0f,0.0f,0.0f);

	//Matrix2D rotation(cos(0.0),-sin(5.0), 0.0f,
	//			      sin(0.0), cos(0.0), 0.0f,
	//				  0.0f, 0.0f, 1.0f);

	//for (int i = 0; i < 20; i++)
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		//_vertex[i] = transform * _vertex[i];
	//	}

	//	_rasterizer->DrawSquare(_vertex);
	//}

	//_rasterizer->DrawSquare(_vertex);

	//Matrix2D _matrix(1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f);

	//Matrix3D testMatrix(0.0f,1.0f,2.0f,3.0f,
	//					3.0f,3.0f,4.0f,5.0f,
	//					1.0f,1.5f,3.5f,1.0f,
	//					5.0f,1.0f,1.0f,1.0f);

	//Matrix3D testMatrix_two(0.0f,1.0f,2.0f,3.0f,
	//					3.0f,3.0f,4.0f,5.0f,
	//					1.0f,1.5f,3.5f,1.0f,
	//					5.0f,1.0f,1.0f,1.0f);


	//Vertex vertexTest(1.0f,2.0f,1.0f,3.0f);

	//vertexTest = testMatrix * vertexTest;

	//testMatrix = testMatrix * testMatrix_two;

	//// Ensure that Windows is told that the contents of the window now needs painting

	//Matrix2D testTwo(1.0f,1.0f,1.0f,
	//				 2.0f,2.0f,3.0f,
	//				 4.0f,4.0f,4.0f);

	//Matrix2D testThree(1.0f,3.0f,4.0f,
	//				   9.0f,1.0f,1.0f,
	//				   2.0f,2.0f,2.0f);

	//testThree = testThree * testTwo;




	/*this->_model.ApplyTransformToLocalVertices(rotateY);
	this->_model.ApplyTransformToTransformedVertices(_camera.ViewpointTransformation());*/
	this->_model.CalculateBackfaces(_camera.GetPosition());
	this->_model.CalculateAmbientLight(_camera.GetPosition(), this->_ambientLight); // Calculate ambient light based off the object value here
	this->_model.CalculateLightingDirectional(_camera.GetPosition(),_directionalLights);
	this->_model.ApplyTransformToTransformedVertices(this->_camera.ViewpointTransformation());
	this->_model.Sort(); // Now that the values have been put into the transformed list, lets sort them from largest to smallest!
	this->_model.ApplyTransformToTransformedVertices(this->_camera.PerspectiveTransformation());
	this->_model.Dehomogenize();
	this->_model.ApplyTransformToTransformedVertices(this->_camera.ScreenTransformation());
	
	// Gouraud Shading
	this->_model.CalculateNormalVector(); // Find the normals for the colour and the vector
	this->_model.CalculateLightingDirectional_Vertex(_camera.GetPosition(),_directionalLights);

	//this->_model.CalculateNormalVector(); // For calculating the normal for each vertex within a polygon
	
	if (_demoMode)
	{
		if (_demoTicker > 500) // 500 ticks being our time limit for each frame of displaying
		{
			_demoTicker = 0;

			if (_modeIndex >= 5)
			{
				_modeIndex = 1;
			}
			else
			{
				_modeIndex++;
			}
		}
		
		_rasterizer->DrawDemoText(_modeIndex);
			

		switch(_modeIndex)
		{
			// Wireframe
		case 1:
			_rasterizer->DrawWireframe(_model);
			break;

			// Wireframe backface
		case 2:
			_rasterizer->DrawWireframeBackface(_model);
			break;

			// Fill Polygon
		case 3:
			_rasterizer->DrawSolidFill(_model);
			break;

			// Flat shading
		case 4:
			_rasterizer->DrawSolidGDIFlat(_model);
			break;

		case 5:
			_rasterizer->DrawSolidFlat(_model);
			break;
		}

		_demoTicker += 5;
	}
	else
	{
		//_rasterizer->DrawSolidFlat(_model);

		//_rasterizer->DrawSolidGDIFlat(_model);

		_rasterizer->DrawSolidGoraud(_model);
	}

	//_rasterizer->DrawDemoText((int) _mode);


	// Increase the rotation per frame
	
	if (bXaxis)
	{
		if (x_axis >= 360)
		{
			x_axis = 0;
		}
		
		x_axis += _speed;
	}

	if (bYaxis)
	{
		if (y_axis >= 360)
		{
			y_axis = 0;
		}
		
		y_axis += _speed;
	}
	
	if (bZaxis)
	{
		if (z_axis >= 360)
		{
			z_axis = 0;
		}
		
		z_axis += _speed;
	}	
	

	InvalidateRect(_hWnd, NULL, FALSE);
}

void AppEngine::Paint(HDC hdc)
{
	// Copy the contents of the rasterizer's bitmap to our window
	if (_rasterizer)
	{
		Graphics graphics(hdc);
		graphics.DrawImage(_rasterizer->GetBitmap(), 0, 0, _rasterizer->GetWidth(), _rasterizer->GetHeight());
	}
}

// Mutator for getting lights
const std::vector<DirectionalLight>& AppEngine::GetLights() const
{
	return this->_directionalLights;
}

void AppEngine::Shutdown(void)
{
	// Clean up all memory that has been dynamically allocated
	if (_rasterizer)
	{
		delete _rasterizer;
		_rasterizer = NULL;
	}
}

const Model3D& AppEngine::GetModel() const
{
	return this->_model;
}