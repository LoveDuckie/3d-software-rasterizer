#include "stdafx.h"
#include "WindowsFileSystem.h"

WindowsFileSystem::WindowsFileSystem()
{
}

WindowsFileSystem::~WindowsFileSystem()
{
}

const bool WindowsFileSystem::FileExists(const char* const absoluteFilePath)
{
	return false;
}

const char* const WindowsFileSystem::CreateDirectory(const char* absoluteFilePath)
{
	return nullptr;
}
