#pragma once
#include "Model3D.h"
#include "IModelImporter.h"

class FBXModelImporter : public IModelImporter
{
public:
	FBXModelImporter();
	virtual ~FBXModelImporter();
protected:
	virtual Model3D* const OnImport(const char* const absoluteFilePath) override;
};