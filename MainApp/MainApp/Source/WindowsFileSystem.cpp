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
	WIN32_FIND_DATAA findData;
	HANDLE findFileHandle = FindFirstFileA(absoluteFilePath, &findData);
	return false;
}

const char* const WindowsFileSystem::CreateDirectory(const char* absoluteFilePath)
{
	return nullptr;
}
