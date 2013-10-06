#pragma once
#include "Rasterizer.h"
#include "Camera.h"
#include "Matrix3D.h"
#include "Model3D.h"
#include "MD2Loader.h"
#include "OBJLoader.h"
#include "DirectionalLight.h"
#include "AmbientLight.h" // Delicious lighting :3
#include <string>


using namespace std;
using namespace Framework::Utility;

namespace Framework
{

	class AppEngine
	{
		public:
			AppEngine(void);
			virtual ~AppEngine(void);

			const AppEngine& operator=(const AppEngine& other);

			void Initialise(HWND hWnd);
			void Process(void);
			void Paint(HDC hdc);
			void Shutdown(void);

			void RotateZ(float degrees);
			void RotateY(float degrees);
			void RotateX(float degrees);

			void ChangeRotation(std::string _type);
			void ChangeSpeed(int _newspeed);

			const std::vector<DirectionalLight>& GetLights() const;
		
			const AmbientLight GetAmbientLight();
			void SetAmbientLight(AmbientLight ambLight);

			const Model3D& GetModel() const;
			const Camera& GetCamera() const;

		private:
			HWND _hWnd;
			Rasterizer * _rasterizer;

			Camera _camera;

			Model3D _model;

			std::vector<DirectionalLight> dLights;
			AmbientLight _amblight;
		
			void Render(void);
	};

}