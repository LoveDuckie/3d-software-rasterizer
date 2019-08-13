#include "stdafx.h"
#include "Model3D.h"
#include <algorithm>
#include <GdiPlus.h>

Model3D::Model3D(void)
{
	// Do nothing, default lists are already initialised
	for (int i = 0; i < (sizeof(this->ka) / sizeof(this->ka[0])); i++)
	{
		ka[i] = 1.0f;
	}

	for (int j = 0; j < (sizeof(this->ks) / sizeof(this->ks[0])); j++)
	{
		ks[j] = 1.0f;
	}

	for (int k = 0; k < (sizeof(this->kd) / sizeof(this->kd[0])); k++)
	{
		kd[k] = 1.0f;
	}

}

Model3D::Model3D(const Model3D& rhs) : _vertexList(rhs._vertexList), 
	_polygonList(rhs._polygonList), 
	_transformedVertexList(rhs._transformedVertexList), 
	_xRotation(rhs._xRotation),
	_yRotation(rhs._yRotation),
	_zRotation(rhs._zRotation)
{

}

Model3D::~Model3D(void)
{
	// Destructor
}

// Boolean sorter function
bool valueGreater(Polygon3D& elem1, Polygon3D& elem2)
{
	return fabs(elem1.GetAverage()) > fabs(elem2.GetAverage());
}

// Mutators
void Model3D::SetPolygon(int value_one, int value_two, int value_three)
{
	Polygon3D _temp;

	_temp.SetValue(0,value_one);
	_temp.SetValue(1,value_two);
	_temp.SetValue(2,value_three);

	this->_polygonList.push_back(_temp);
}

void Model3D::SetVertex(float x, float y, float z, float w)
{
	Vertex _temp;

	_temp.SetX(x);
	_temp.SetY(y);
	_temp.SetZ(z);
	_temp.SetW(w);

	this->_vertexList.push_back(_temp);
	//this->transformedVertexList[index] = other;
}

// Transformation Methods
void Model3D::ApplyTransformToLocalVertices(const Matrix3D& transform)
{
	Vertex tempVert;

	_transformedVertexList.clear();

	// Loop through the vertices and modify accordingly.
	for (int i = 0; i < (int) _vertexList.size(); i++)
	{
		tempVert = transform * _vertexList[i];
		this->_transformedVertexList.push_back(tempVert);
	}
	
}

// Sorting to sort out the issue with the backface culling
void Model3D::Sort(void)
{
	Vertex A, B, C;
	int index_1, index_2, index_3;
	float temp = 0.0f;

	for (int i = 0; i < (int) this->_polygonList.size(); i++)
	{
		index_1 = this->_polygonList[i].GetValue(0);
		index_2 = this->_polygonList[i].GetValue(1);
		index_3 = this->_polygonList[i].GetValue(2);

		A = this->_transformedVertexList[index_1];
		B = this->_transformedVertexList[index_2];
		C = this->_transformedVertexList[index_3];
		
		temp = ((A.GetZ() + B.GetZ() + C.GetZ()) / 3);

		this->_polygonList[i].SetAverage(temp);
	}

	// Using the sort function, make use of the valueGreater boolean function to make comparisons.
	std::sort(this->_polygonList.begin( ),this->_polygonList.end( ), valueGreater);
}

// Multiply the give matrix to the list of transformed vertices.

void Model3D::ApplyTransformToTransformedVertices(const Matrix3D& transform)
{
	for (int i = 0; i < (int) this->_transformedVertexList.size(); i++)
	{
		this->_transformedVertexList[i] = transform * this->_transformedVertexList[i];
	}
}

void Model3D::CalculateAmbientLight(const Vertex &cameraPosition, AmbientLight ambLight)
{
	int temp_a,temp_r,temp_g,temp_b;

	temp_a = 255;

	Gdiplus::ARGB temp_argb;

	for (int i = 0; i < (int) this->_polygonList.size(); i++)
	{
		temp_r = ambLight.GetColor().GetR();
		temp_g = ambLight.GetColor().GetG();
		temp_b = ambLight.GetColor().GetB();

	    temp_r = (int) (temp_r * this->GetKaComponent(0));
		temp_g = (int) (temp_g * this->GetKaComponent(1));
		temp_b = (int) (temp_b * this->GetKaComponent(2));
		
		temp_r = (temp_r > 255 ? 255 : (temp_r < 0 ? 0 : temp_r));
		temp_g = (temp_g > 255 ? 255 : (temp_g < 0 ? 0 : temp_g));
		temp_b = (temp_b > 255 ? 255 : (temp_b < 0 ? 0 : temp_b));

		temp_argb = Color::MakeARGB(temp_a, temp_r, temp_g, temp_b);
		this->_polygonList[i].SetColor(temp_argb);
	}


	// Setting default ambient lighting for Vertices
	for (int j = 0; j < (int) this->_transformedVertexList.size(); j++)
	{
		temp_r = ambLight.GetColor().GetR();
		temp_g = ambLight.GetColor().GetG();
		temp_b = ambLight.GetColor().GetB();

	    temp_r = (int) (temp_r * this->GetKaComponent(0));
		temp_g = (int) (temp_g * this->GetKaComponent(1));
		temp_b = (int) (temp_b * this->GetKaComponent(2));
		
		temp_r = (temp_r > 255 ? 255 : (temp_r < 0 ? 0 : temp_r));
		temp_g = (temp_g > 255 ? 255 : (temp_g < 0 ? 0 : temp_g));
		temp_b = (temp_b > 255 ? 255 : (temp_b < 0 ? 0 : temp_b));

		temp_argb = Color::MakeARGB(temp_a, temp_r, temp_g, temp_b);
		this->_transformedVertexList[j].SetColor(temp_argb);
	}
}

// Producing the colours for each polygon vertex.
void Model3D::CalculateLightingDirectional_Vertex(const Vertex &cameraPosition, std::vector<DirectionalLight> dirLights)
{
	// Total lighting
	int total_a,total_r,total_g,total_b;
	
	// Temporary
	int temp_a,temp_r,temp_g,temp_b;

	Gdiplus::ARGB temp_argb;
	
	Vector3D temp_light_normal;

	float temp_dot_product;

	for (int i = 0; i < (int) this->_transformedVertexList.size(); i++)
	{
		total_a = 255;
		total_r = this->_transformedVertexList[i].GetColor().GetR();
		total_g = this->_transformedVertexList[i].GetColor().GetG();
		total_b = this->_transformedVertexList[i].GetColor().GetB();

		for (int j = 0; j < (int) dirLights.size(); j++)
		{
			temp_a = dirLights[j].GetColor().GetAlpha();
			temp_r = dirLights[j].GetColor().GetRed();
			temp_g = dirLights[j].GetColor().GetGreen();
			temp_b = dirLights[j].GetColor().GetBlue();
			
			temp_r = (int) (temp_r * this->GetKdComponent(0)); // Get the directional light co-efficient for R/G/B
			temp_g = (int) (temp_g * this->GetKdComponent(1));
			temp_b = (int) (temp_b * this->GetKdComponent(2));

			temp_light_normal = dirLights[j].GetPosition().Normalise();


			temp_dot_product = Model3D::Dot(temp_light_normal,_transformedVertexList[i].GetNormal());

			temp_r = (int)(temp_r * temp_dot_product);
			temp_g = (int)(temp_g * temp_dot_product);
			temp_b = (int)(temp_b * temp_dot_product);
				
			// Add 'em up!

			total_r += temp_r;
			total_g += temp_g;
			total_b += temp_b;
		}

		total_r = (total_r > 255 ? 255 : (total_r < 0 ? 0 : total_r));
		total_g = (total_g > 255 ? 255 : (total_g < 0 ? 0 : total_g));
		total_b = (total_b > 255 ? 255 : (total_b < 0 ? 0 : total_b));

		total_a = 255;

		temp_argb = Color::MakeARGB(total_a,total_r,total_g,total_b);

		this->_transformedVertexList[i].SetColor(temp_argb);
	}
}

void Model3D::CalculateLightingDirectional(const Vertex &cameraPosition, std::vector<DirectionalLight> dirLights)
{
	// Total lighting
	int total_a,total_r,total_g,total_b;
	
	// Temporary
	int temp_a,temp_r,temp_g,temp_b;

	Gdiplus::ARGB temp_argb;

	Vector3D temp_light_normal;

	float temp_dot_product;


	for (int i = 0; i < (int) this->_polygonList.size(); i++)
	{
		total_a = 255;
		total_r = this->_polygonList[i].GetColor().GetR();
		total_g = this->_polygonList[i].GetColor().GetG();
		total_b = this->_polygonList[i].GetColor().GetB();

		for (int j = 0; j < (int) dirLights.size(); j++)
		{
			temp_a = dirLights[j].GetColor().GetA();
			temp_r = dirLights[j].GetColor().GetR();
			temp_g = dirLights[j].GetColor().GetG();
			temp_b = dirLights[j].GetColor().GetB();

			temp_r = (int) (temp_r * this->GetKdComponent(0));
			temp_g = (int) (temp_g * this->GetKdComponent(1));
			temp_b = (int) (temp_b * this->GetKdComponent(2));

			//float test_float = this->GetKdComponent(0);

			temp_light_normal = dirLights[j].GetPosition().Normalise();

			//negative = Vector3D(-temp_light_normal.GetX(),-temp_light_normal.GetY(),-temp_light_normal.GetZ());

			// Generating the dot product from: DIRECTION LIGHT NORMAL & POLYGON NORMAL
			temp_dot_product = Model3D::Dot(temp_light_normal,_polygonList[i].GetNormal());

			temp_r = (int)(temp_r * temp_dot_product);
			temp_g = (int)(temp_g * temp_dot_product);
			temp_b = (int)(temp_b * temp_dot_product);
				
			total_r += temp_r;
			total_g += temp_g;
			total_b += temp_b;

			total_a = 255;
			// Adding up the totals.
		}

		total_r = (total_r > 255 ? 255 : (total_r < 0 ? 0 : total_r));
		total_g = (total_g > 255 ? 255 : (total_g < 0 ? 0 : total_g));
		total_b = (total_b > 255 ? 255 : (total_b < 0 ? 0 : total_b));

		// Create temp ARGB
		temp_argb = Color::MakeARGB(total_a,total_r,total_g,total_b);

		// Store back into polygon
		this->_polygonList[i].SetColor(temp_argb);
	}
}

Polygon3D& Model3D::GetPolygon(int i)
{
	return this->_polygonList[i];
}

Vertex& Model3D::GetVertex(int i)
{
	return this->_vertexList[i];
}

void Model3D::CalculateNormalVector()
{
	// Creating some needed temporary vars.
	Vertex _one, _two, _three;
	Vector3D A,B;
	Polygon3D _tempPoly;
	Vector3D _polyNormal;

	// Basic ints to store the vertex indexes from the polygon
	int _indexOne, _indexTwo, _indexThree;

	for (int i = 0; i < (int) this->_transformedVertexList.size(); i++)
	{
		_transformedVertexList[i].SetNormal(Vector3D(0,0,0));
		_transformedVertexList[i].SetNormalContribCount(0);
	}

	for (int j = 0; j < (int) this->_polygonList.size(); j++)
	{
		// Storing the poly as a temp value to prevent repetitive calls
		_tempPoly = this->_polygonList[j];
		_indexOne = _tempPoly.GetValue(0);
		_indexTwo = _tempPoly.GetValue(1);
		_indexThree = _tempPoly.GetValue(2);
		
		// Getting the vertices with the newly found indexes
		_one = this->_transformedVertexList[_indexOne];
		_two = this->_transformedVertexList[_indexTwo];
		_three = this->_transformedVertexList[_indexThree];

		//// Now finding the normal of the polygon face (again)
		A = _one.Subtract(_two);
		B = _one.Subtract(_three);

		_polyNormal = Model3D::Cross(A,B);
		this->_polygonList[j].SetNormal(_polyNormal);
	
		// Figure out the vertex normals here
		_one.SetNormal(_one.GetNormal() + _polyNormal);
		_one.BumpNormalContribCount();
		_two.SetNormal(_two.GetNormal() + _polyNormal);
		_two.BumpNormalContribCount();
		_three.SetNormal(_three.GetNormal() + _polyNormal);
		_three.BumpNormalContribCount();

		// Put back in our new & lovely created temp vertices
		this->_transformedVertexList[_indexOne] = _one;
		this->_transformedVertexList[_indexTwo] = _two;
		this->_transformedVertexList[_indexThree] = _three;
	}

	for (int k = 0; k < (int) this->_transformedVertexList.size(); k++)
	{
		Vector3D _normalTemp;

		_normalTemp = this->_transformedVertexList[k].GetNormal();
		_normalTemp.DivideByInt(_transformedVertexList[k].GetNormalContribCount());
		
		// Do the normalisation here
		_normalTemp.Normalise();

		// Put our temp value back into the normal of the vertex.
		this->_transformedVertexList[k].SetNormal(_normalTemp);
	}

}

// Fix this later
//const Model3D& Model3D::operator= (const Model3D& other)
//{
//	this->polygonList.clear();
//	this->vertexList.clear();
//
//	for (int i = 0; i < other.polygonList.size(); i++)
//	{
//		this->polygonList[i] = other.polygonList[i];
//		this->vertexList[i] = other.vertexList[i];
//		this->transformedVertexList[i] = other.transformedVertexList[i];
//	}
//
//	return *this;
//}

// Changing list sizes to conserve a bit of memory.
void Model3D::ResizePolygons(int value)
{
	this->_polygonList.resize(value);
}


void Model3D::Reset()
{
	// DESTROYYYYYY EVERYTHING! D:
	
	this->_polygonList.clear();
	this->_vertexList.clear();
	this->_transformedVertexList.clear();
}

// Changing list sizes to conserve a bit of memory.
void Model3D::ResizeVertices(int value)
{
	this->_vertexList.resize(value);
}

void Model3D::Dehomogenize()
{
	for (int i = 0; i < (int) this->_vertexList.size(); i++)
	{
		this->_transformedVertexList[i].Dehomogenize();
	}
}

std::vector<Vertex>& Model3D::GetTransformedVertices()
{
	return this->_transformedVertexList;
}

const Vertex Model3D::GetTransformedVertex(int i)
{
	return this->_transformedVertexList[i];
}

std::vector<Vertex>& Model3D::GetVertices()
{
	return this->_vertexList;
}

std::vector<Polygon3D>& Model3D::GetPolygons()
{
	return this->_polygonList;
}

// GETTERS

const float& Model3D::GetXRotation(void) const
{
	return this->_xRotation;
}

const float& Model3D::GetYRotation(void) const
{
	return this->_yRotation;
}

const float Model3D::GetZRotation()
{
	return this->_zRotation;
}

Vector3D Model3D::Cross(const Vector3D& other_one, const Vector3D& other_two)
{
	return  Vector3D(other_one.GetY() * other_two.GetZ() - other_two.GetY() * other_one.GetZ(),
					 other_one.GetZ() * other_two.GetX() - other_two.GetZ() * other_one.GetX(),
					 other_one.GetX() * other_two.GetY() - other_two.GetX() * other_one.GetY());
}

float Model3D::Dot(Vector3D other_one, Vector3D other_two)
{
	return ((other_one.GetX() * other_two.GetX()) + (other_one.GetY() * other_two.GetY()) + (other_one.GetZ() * other_two.GetZ()));
}


void Model3D::CalculateBackfaces(const Vertex &cameraPosition)
{
	Vector3D vectorNormal, eyeVector;
	Vertex _one, _two, _three; // Temp vars for Vertices

	Vector3D A;
	Vector3D B;

	float finalDotProduct = 0.0f;

	for (int i = 0; i < (int) this->_polygonList.size(); i++)
	{
		_one = this->_transformedVertexList[this->_polygonList[i].GetValue(0)];
		_two = this->_transformedVertexList[this->_polygonList[i].GetValue(1)];
		_three = this->_transformedVertexList[this->_polygonList[i].GetValue(2)];

		// Define the two Vectors by substracting individual Vertices by themselves.
		
		A = _one.Subtract(_two);
		B = _one.Subtract(_three);
		
		// Check the cross product
		vectorNormal = Model3D::Cross(A,B);

		// Storing the normal of polygons
		this->_polygonList[i].SetNormal(vectorNormal);
		
		// Get the eye vector by subtracting one more time with the camera position
		eyeVector = _one.Subtract(cameraPosition);
		
		// Get the last dot product.
		finalDotProduct = Model3D::Dot(vectorNormal, eyeVector);

		// Base the dot product based on where it is looking backwards or not.
		if (finalDotProduct < 0.0f)
			this->_polygonList[i].SetBackfacing(true);
		else
			this->_polygonList[i].SetBackfacing(false);

	}
}

float Model3D::GetKdComponent(int index) const
{
		return this->kd[index];
}

float Model3D::GetKaComponent(int index) const
{
		return this->ka[index];
}

float Model3D::GetKsComponent(int index) const
{
	//if (index <= 2 && index >= 0)
		return this->ks[index];
}

// Index defines which RGB reflection component we wish to modify.
void Model3D::SetKdComponent(int index, float value)
{
		this->kd[index] = value;
}

void Model3D::SetKaComponent(int index, float value)
{
		this->ka[index] = value;
}

void Model3D::SetKSComponent(int index, float value)
{
		this->ks[index] = value;
}