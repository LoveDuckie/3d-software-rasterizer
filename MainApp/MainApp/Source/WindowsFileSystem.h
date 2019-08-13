#pragma once
#include "IFileSystem.h"

class WindowsFileSystem : public IFileSystem
{
public:
	WindowsFileSystem();
	~WindowsFileSystem();

	// Inherited via FileSystem
	virtual const bool FileExists(const char* const absoluteFilePath) override;
	virtual const char* const CreateDirectory(const char* const absoluteFilePath);
};