#include "stdafx.h"
#include "Camera.h"

Camera::Camera(
	    float xRotation, float yRotation, float zRotation,
		const Vertex& position,
		unsigned int viewWidth,
		unsigned int viewHeight
		)
{
	this->x_rotation = xRotation;
	this->y_rotation = yRotation;
	this->z_rotation = zRotation;
	
	this->_viewHeight = viewHeight;
	this->_viewWidth = viewWidth;
	
	this->_position = position;

	this->viewpointTransformation = Matrix3D();
	this->screenTransformation = Matrix3D();
	this->perspectiveTransformation = Matrix3D();

	

	// Projection Matrix
	this->screenTransformation = Matrix3D( (_viewWidth / 2.0f), 0.0f, 0.0f, (_viewWidth / 2.0f),
										  0.0f, -(_viewHeight / 2.0f), 0.0f, (_viewHeight / 2.0f),
										  0.0f, 0.0f, 1.0f, 0.0f,
										  0.0f, 0.0f, 0.0f, 1.0f);

	// View Matrix -- Perform transformations on the camera.
	this->viewpointTransformation =      	 Matrix3D(1.0f, 0.0f, 0.0f, 0.0f,
													  0.0f, cos(x_rotation), sin(x_rotation), 0.0f, // X Axis Rotation
													  0.0f, -sin(x_rotation), cos(x_rotation), 0.0f,
													  0.0f, 0.0f, 0.0f, 1.0f)
											 *
											 Matrix3D(cos(y_rotation),0.0f, -sin(y_rotation), 0.0f, // Y Axis Rotation
													  0.0f, 1.0f, 0.0f, 0.0f,
													  sin(y_rotation), 0.0f, cos(y_rotation), 0.0f,
													  0.0f, 0.0f, 0.0f, 1.0f)
											 *
											 Matrix3D(cos(z_rotation), sin(z_rotation), 0.0f, 0.0f, // Z Axis Rotation
													 -sin(z_rotation), cos(z_rotation), 0.0f, 0.0f,
											   		 0.0f, 0.0f, 1.0f, 0.0f,
													 0.0f, 0.0f, 0.0f, 1.0f)

											*

											// Translating the last part of the camera
											Matrix3D(1,0,0, -_position.GetX(),
													 0,1,0, -_position.GetY(),
													 0,0,1, -_position.GetZ(),
													 0,0,0,1);

	

	this->perspectiveTransformation = Matrix3D(1.0f, 0.0f, 0.0f, 0.0f,
											   0.0f, 1.0f, 0.0f, 0.0f,
											   0.0f, 0.0f, 1.0f, 0.0f,
											   0.0f, 0.0f, 1.0f, 0.0f);

	// Need to define matrices here
}

Camera::~Camera(void)
{
	// Do nothing yet

	this->_position = Vertex();
}

Camera::Camera(void)
{
	_viewWidth = 480;
	_viewHeight = 640;

	x_rotation = 0.0f;
	y_rotation = 0.0f;
	z_rotation = 0.0f;

	this->_position = Vertex(0.0f,0.0f,0.0f,-0.50f); // 3rd value is "W" remember

	// Setting up default values
	this->perspectiveTransformation = Matrix3D();
	this->screenTransformation = Matrix3D();
	this->viewpointTransformation = Matrix3D();
}

// Getters

const int& Camera::GetViewHeight() const
{
	return this->_viewHeight;
}

const int& Camera::GetViewWidth() const
{
	return this->_viewWidth;
}

const float Camera::GetXRotation()
{
	return this->x_rotation;
}

const float Camera::GetYRotation()
{
	return this->y_rotation;
}

const float Camera::GetZRotation()
{
	return this->z_rotation;
}

const Vertex Camera::GetPosition()
{
	return this->_position;
}

const Matrix3D Camera::ViewpointTransformation()
{
	return this->viewpointTransformation;
}

const Matrix3D Camera::PerspectiveTransformation()
{
	return this->perspectiveTransformation;
}

const Matrix3D Camera::ScreenTransformation()
{
	return this->screenTransformation;
}

// Setters

void Camera::SetXRotation(const float& value)
{
	this->x_rotation = value;
}

void Camera::SetYRotation(const float& value)
{
	this->y_rotation = value;
}

void Camera::SetZRotation(const float& value)
{
	this->z_rotation = value;
}

void Camera::SetPosition(const Vertex& pos)
{
	this->_position = pos;
}

void Camera::SetViewHeight(const int& value)
{
	this->_viewHeight = value;
}

void Camera::SetViewWidth(const int& value)
{
	this->_viewWidth = value;
}