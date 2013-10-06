#pragma once
#include "Model3D.h"
#include <fstream>

using namespace std;

namespace Framework
{
	namespace Utility
	{
		class OBJLoader
		{
		public:
			static Model3D Load(const char* pFilename);
			static bool Load(const char* pFilename, Model3D& pModel);
		};
	}
}