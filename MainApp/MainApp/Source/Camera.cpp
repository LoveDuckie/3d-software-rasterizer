#include "stdafx.h"
#include "Camera.h"
#include "AppEngineConstants.h"

Camera::Camera(
	    float xRotation, float yRotation, float zRotation,
		const Vertex& position,
		unsigned int viewWidth,
		unsigned int viewHeight)
{
	this->_xRotation = xRotation;
	this->_yRotation = yRotation;
	this->_zRotation = zRotation;
	
	this->_viewHeight = viewHeight;
	this->_viewWidth = viewWidth;
	
	this->_position = position;

	this->_viewpointTransformation = Matrix3D();
	this->_screenTransformation = Matrix3D();
	this->_perspectiveTransformation = Matrix3D();

	// Projection Matrix
	this->_screenTransformation = Matrix3D( (_viewWidth / 2.0f), 0.0f, 0.0f, (_viewWidth / 2.0f),
										  0.0f, -(_viewHeight / 2.0f), 0.0f, (_viewHeight / 2.0f),
										  0.0f, 0.0f, 1.0f, 0.0f,
										  0.0f, 0.0f, 0.0f, 1.0f);

	// View Matrix -- Perform transformations on the camera.
	this->_viewpointTransformation =      	 Matrix3D(1.0f, 0.0f, 0.0f, 0.0f,
													  0.0f, cos(_xRotation), sin(_xRotation), 0.0f, // X Axis Rotation
													  0.0f, -sin(_xRotation), cos(_xRotation), 0.0f,
													  0.0f, 0.0f, 0.0f, 1.0f)
											 *
											 Matrix3D(cos(_yRotation),0.0f, -sin(_yRotation), 0.0f, // Y Axis Rotation
													  0.0f, 1.0f, 0.0f, 0.0f,
													  sin(_yRotation), 0.0f, cos(_yRotation), 0.0f,
													  0.0f, 0.0f, 0.0f, 1.0f)
											 *
											 Matrix3D(cos(_zRotation), sin(_zRotation), 0.0f, 0.0f, // Z Axis Rotation
													 -sin(_zRotation), cos(_zRotation), 0.0f, 0.0f,
											   		 0.0f, 0.0f, 1.0f, 0.0f,
													 0.0f, 0.0f, 0.0f, 1.0f)

											*

											// Translating the last part of the camera
											Matrix3D(1,0,0, -_position.GetX(),
													 0,1,0, -_position.GetY(),
													 0,0,1, -_position.GetZ(),
													 0,0,0,1);

	

	this->_perspectiveTransformation = Matrix3D(1.0f, 0.0f, 0.0f, 0.0f,
											   0.0f, 1.0f, 0.0f, 0.0f,
											   0.0f, 0.0f, 1.0f, 0.0f,
											   0.0f, 0.0f, 1.0f, 0.0f);

	// Need to define matrices here
}

Camera::~Camera(void)
{
}

Camera::Camera(void) : _viewWidth(Framework::AppEngineConstants::CameraViewportWidth), 
						_viewHeight(Framework::AppEngineConstants::CameraViewportHeight)
{
	_xRotation = 0.0f;
	_yRotation = 0.0f;
	_zRotation = 0.0f;

	this->_position = Vertex(0.0f,0.0f,0.0f,-0.50f); // 3rd value is "W" remember

	// Setting up default values
	this->_perspectiveTransformation = Matrix3D();
	this->_screenTransformation = Matrix3D();
	this->_viewpointTransformation = Matrix3D();
}

// Getters

const unsigned int& Camera::GetViewHeight() const
{
	return this->_viewHeight;
}

const unsigned int& Camera::GetViewWidth() const
{
	return this->_viewWidth;
}

const float Camera::GetXRotation()
{
	return this->_xRotation;
}

const float Camera::GetYRotation()
{
	return this->_yRotation;
}

const float Camera::GetZRotation()
{
	return this->_zRotation;
}

const Vertex Camera::GetPosition()
{
	return this->_position;
}

const Matrix3D& Camera::GetViewpointTransformation() const
{
	return this->_viewpointTransformation;
}

const Matrix3D& Camera::GetPerspectiveTransformation() const
{
	return this->_perspectiveTransformation;
}

const Matrix3D& Camera::GetScreenTransformation() const
{
	return this->_screenTransformation;
}

void Camera::SetXRotation(const float& value)
{
	this->_xRotation = value;
}

void Camera::SetYRotation(const float& value)
{
	this->_yRotation = value;
}

void Camera::SetZRotation(const float& value)
{
	this->_zRotation = value;
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