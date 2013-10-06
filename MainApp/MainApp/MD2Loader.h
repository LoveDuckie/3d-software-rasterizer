#pragma once
#include "Model3D.h"

// Forward reference
class Model3D;

class MD2Loader
{
	public:
		MD2Loader(void);
		~MD2Loader(void);
		static bool LoadModel(const char* md2Filename, Model3D& model);
};
