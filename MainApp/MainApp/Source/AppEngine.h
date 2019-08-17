#ifndef AppEngine_h__
#define AppEngine_h__

#pragma once
#include "Rasterizer.h"
#include "Camera.h"
#include "Matrix3D.h"
#include "Model3D.h"
#include "MD2Loader.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include <string>
#include "IModelImporter.h"

using namespace std;

namespace Framework
{
	// The various types that the app engine can rotate on 
	enum class AppEngineRotationTypes
	{
		XAxis,
		YAxis,
		ZAxis
	};

	class AppEngine
	{
	public:
		AppEngine();
		~AppEngine();

	private:
		AppEngine& operator=(const AppEngine& rhs) = delete;
		AppEngine(const AppEngine& rhs) = delete;

	public:

		void Initialise(HWND hWnd);
		void Process(const double& deltaTimeMs);
		void Paint(HDC hdc);
		void Shutdown(void);

		void RotateZ(const float& degrees);
		void RotateY(const float& degrees);
		void RotateX(const float& degrees);

		IModelImporter* const CreateImporter(const char* const absoluteFilePath);

		void SetRotationType(std::string _type);
		void SetRotationSpeed(int _newspeed);

		const std::vector<DirectionalLight>& GetLights() const;
		
		const AmbientLight GetAmbientLight();
		void SetAmbientLight(const AmbientLight& ambLight);

		const Model3D& GetModel() const;
		const Camera& GetCamera() const;

	private:
		HWND			_hWnd;
		Rasterizer*		_rasterizer;

		Camera		_camera;
		Model3D		_model;

		IModelImporter* _importer;

		std::vector<DirectionalLight> _directionalLights;
		AmbientLight _ambientLight;
		
		void Render(void);
	};

}
#endif // AppEngine_h__