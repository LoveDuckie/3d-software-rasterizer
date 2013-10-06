#include "OBJLoader.h"

using namespace Framework::Utility;
using namespace std;


bool OBJLoader::Load(const char* pFilename, Model3D& pModel)
{
	ifstream modelFile(pFilename,ios::binary | ios::in);

	// Begin to the load the file
	if (!modelFile.fail())
	{


		return true;
	}

	return false;
}