#pragma once


class IFileSystem
{
public:
	IFileSystem() = default;
	virtual ~IFileSystem() = default;

	virtual const bool FileExists(const char* const absoluteFilePath) = 0;
	virtual const char* const CreateDirectory(const char* const absoluteFilePath) = 0;
	const bool TryCreateDirectory(const char* const absoluteFilePath);
private:
};