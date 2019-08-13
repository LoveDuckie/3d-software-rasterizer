#pragma once
#include "IModelImporter.h"

class MD2ModelImporter : public IModelImporter
{
	// Inherited via ModelImporter
	virtual const Model3D* OnImport(const char* const absoluteFilePath) override;
};