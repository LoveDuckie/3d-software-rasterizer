#include "stdafx.h"
#include "Vertex.h"
#include "Matrix3D.h"
#include "Polygon3D.h"
#include <math.h>

class Camera
{
public:
	Camera();
	~Camera();
	Camera(float xRotation, float yRotation, float zRotation,
		const Vertex& position,
		unsigned int viewWidth,
		unsigned int viewHeight);

	const int& GetViewHeight() const;
	const int& GetViewWidth() const;
		
	const float GetXRotation();
	const float GetYRotation();
	const float GetZRotation();

	const Vertex GetPosition();

	// Setters
	void SetXRotation(const float& value);
	void SetYRotation(const float& value);
	void SetZRotation(const float& value);
	
	void SetViewHeight(const int& value);
	void SetViewWidth(const int& value);

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