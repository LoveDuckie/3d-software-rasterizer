#pragma once
#include <vector>
#include <GdiPlus.h>
#include <math.h>
#include <Windows.h>

#include "Polygon3D.h"
#include "Vertex.h"
#include "MD2Loader.h"
#include "Matrix3D.h"
#include "Model3D.h"
#include "Vector3D.h"

#include "DirectionalLight.h"
#include "AmbientLight.h"

// Just so we can access the color objects and draw pretty polygons!
using namespace Gdiplus;

class Model3D
{

public:
	Model3D(); // Constructor
	Model3D(const Model3D& rhs);
	virtual ~Model3D(); // Destructor
	
	//Model3D(const Model3D& model);

	//const Model3D& operator= (const Model3D &other);
	
	Polygon3D& GetPolygon(int i);
	Vertex& GetVertex(int i);

	void ApplyTransformToLocalVertices(const Matrix3D& transform); // Work on this later
	void ApplyTransformToTransformedVertices(const Matrix3D& transform); // Work on this later

	// For tidying up the size of the lists when they're first loaded.
	void ResizePolygons(int value);
	void ResizeVertices(int value);

	// Mutators
	void SetPolygon(int, int, int);
	void SetVertex(float, float, float, float);

	void CalculateLightingDirectional(const Vertex& cameraPosition, std::vector<DirectionalLight> directionalLights);
	void CalculateAmbientLight(const Vertex& cameraPosition, AmbientLight ambientLight);
	void CalculateLightingDirectional_Vertex(const Vertex& cameraPosition, std::vector<DirectionalLight> directionalLights);

	void Dehomogenize();

	void Reset();
	
	// From highest to lowest, sort the values in order.
	void Sort(void);

	//bool valueGreater(float,float);

	void CalculateBackfaces(const Vertex &cameraPosition);

	static Vector3D Cross(const Vector3D& other_one, const Vector3D& other_two);
	static float Dot(Vector3D other_one, Vector3D other_two);

	const Vertex GetTransformedVertex(int i);

	void CalculateNormalVector();

	// Co-efficient mutators
	float GetKdComponent(int index) const;
	float GetKaComponent(int index) const;
	float GetKsComponent(int index) const;

	void SetKdComponent(int index, float value);
	void SetKaComponent(int index, float value);
	void SetKSComponent(int index, float value);

	// Rotation Getters
	const float& GetXRotation(void) const;
	const float& GetYRotation(void) const;
	const float GetZRotation(void);

	// Rotation Setters
	void SetXRotation(float);
	void SetYRotation(float);
	void SetZRotation(float);

	// Fetch privatised vector lists
	std::vector<Vertex>& GetTransformedVertices();
	std::vector<Vertex>& GetVertices();

	std::vector<Polygon3D>& GetPolygons();
	
private:
	 std::vector<Polygon3D> _polygonList;
	 std::vector<Vertex> _vertexList;
	 std::vector<Vertex> _transformedVertexList; // Transformed, keep the original

	 // Rotation vars
	 float _xRotation;
	 float _yRotation;
	 float _zRotation;

	 float kd[3];
	 float ka[3];
	 float ks[3];

	// INDEX ORDER: 0 - RED, 1 - GREEN, 2 - BLUE

	 void Copy(Model3D& other);

};