#pragma once
#include "Model3D.h"

class IModelImporter
{
public:
	IModelImporter() = default;
	virtual ~IModelImporter() = default;
	const Model3D* Import(const char* const absoluteFilePath);
	
protected:
	virtual Model3D* const OnImport(const char* const absoluteFilePath) = 0;
private:
	
};