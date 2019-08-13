#pragma once
#include "Model3D.h"
#include "ModelImporter.h"

class FBXModelImporter : public ModelImporter
{
public:
	FBXModelImporter();
	virtual ~FBXModelImporter();
protected:
	virtual const Model3D* OnImport(const char* const absoluteFilePath);
};