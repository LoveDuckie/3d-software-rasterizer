#pragma once

namespace Framework
{
	class AppEngineConstants
	{
	private:
		AppEngineConstants();
		AppEngineConstants(const AppEngineConstants& rhs);
		~AppEngineConstants();

	public:
		static const int CameraViewportWidth = 640;
		static const int CameraViewportHeight = 480;
	};
}
