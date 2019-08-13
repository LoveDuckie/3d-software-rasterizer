#pragma once
#include "Model3D.h"

class IModelImporter
{
public:
	IModelImporter();
	virtual ~IModelImporter();
	const Model3D* Import(const char* const absoluteFilePath);
	
protected:
	virtual const Model3D* OnImport(const char* const absoluteFilePath) = 0;
private:
	
};