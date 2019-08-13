#pragma once
#include "Rasterizer.h"
#include "Camera.h"
#include "Matrix3D.h"
#include "Model3D.h"
#include "MD2Loader.h"
#include "DirectionalLight.h"
#include "AmbientLight.h" // Delicious lighting :3
#include <string>
#include "ModelImporter.h"

using namespace std;

namespace Framework
{
	class AppEngine
	{
	public:
		AppEngine();
		~AppEngine();

	private:
		AppEngine& operator=(const AppEngine& rhs);
		AppEngine(const AppEngine& rhs);

	public:

		void Initialise(HWND hWnd);
		void Process(const double& deltaTimeMs);
		void Paint(HDC hdc);
		void Shutdown(void);

		void RotateZ(const float& degrees);
		void RotateY(const float& degrees);
		void RotateX(const float& degrees);

		ModelImporter* const CreateImporter(const char* const absoluteFilePath);

		void SetRotationType(std::string _type);
		void SetRotationSpeed(int _newspeed);

		const std::vector<DirectionalLight>& GetLights() const;
		
		const AmbientLight GetAmbientLight();
		void SetAmbientLight(const AmbientLight& ambLight);

		const Model3D& GetModel() const;
		const Camera& GetCamera() const;

	private:
		HWND _hWnd;
		Rasterizer * _rasterizer;

		Camera _camera;
		Model3D _model;

		ModelImporter* _importer;

		std::vector<DirectionalLight> _directionalLights;
		AmbientLight _ambientLight;
		
		void Render(void);
	};

}