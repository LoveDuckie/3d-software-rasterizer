#pragma once
#include "FileSystem.h"

class WindowsFileSystem : public FileSystem
{
public:
	WindowsFileSystem();
	~WindowsFileSystem();

	// Inherited via FileSystem
	virtual const bool FileExists(const char* const absoluteFilePath) override;
	virtual const char* const CreateDirectory(const char* absoluteFilePath);
};