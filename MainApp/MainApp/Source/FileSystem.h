#pragma once


class FileSystem
{
public:
	FileSystem();
	virtual ~FileSystem();

	virtual const bool FileExists(const char* const absoluteFilePath) = 0;
	virtual const char* const CreateDirectory(const char* const absoluteFilePath) = 0;
	const bool TryCreateDirectory(const char* const absoluteFilePath);
private:
};