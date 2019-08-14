#pragma once
#include "IModelImporter.h"

class MD2ModelImporter : public IModelImporter
{
public:
	MD2ModelImporter() = default;
	virtual ~MD2ModelImporter() = default;
protected:
	virtual Model3D* const OnImport(const char* const absoluteFilePath) override;
};