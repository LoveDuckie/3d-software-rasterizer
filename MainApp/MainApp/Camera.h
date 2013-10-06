#include "stdafx.h"
#include "Vertex.h"
#include "Matrix3D.h"
#include "Polygon3D.h"
#include <math.h>

class Camera
{
public:
	// Specified constructor
	Camera(float xRotation, float yRotation, float zRotation,
		const Vertex& position,
		unsigned int viewWidth,
		unsigned int viewHeight);

	// Default
	Camera(void);

	// Destructor
	~Camera(void);
	
	// Getters
	const int GetViewHeight();
	const int GetViewWidth();
		
	const float GetXRotation();
	const float GetYRotation();
	const float GetZRotation();

	const Vertex GetPosition();

	// Setters
	void SetXRotation(float value);
	void SetYRotation(float value);
	void SetZRotation(float value);
	
	void SetViewHeight(int value);
	void SetViewWidth(int value);

	void SetPosition(const Vertex& pos);

	const Matrix3D ViewpointTransformation();

	const Matrix3D PerspectiveTransformation();

	const Matrix3D ScreenTransformation();

private:
	Vertex _position;
	unsigned int _viewHeight; // For dealing with Screen Transformation
	unsigned int _viewWidth;

	float x_rotation;
	float y_rotation;
	float z_rotation;
	
	Matrix3D viewpointTransformation; // Camera transformation
	Matrix3D perspectiveTransformation; // Perspective transformation
	Matrix3D screenTransformation; // Screen transformation (varies on viewwidth & viewheight)
};