#pragma once
#include "Model3D.h"
#include "IModelImporter.h"

class FBXModelImporter : public IModelImporter
{
public:
	FBXModelImporter();
	virtual ~FBXModelImporter();
protected:
	virtual const Model3D* OnImport(const char* const absoluteFilePath);
};