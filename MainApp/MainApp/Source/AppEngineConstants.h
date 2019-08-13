#pragma once

namespace Framework
{
	class AppEngineConstants
	{
	private:
		AppEngineConstants() = default;
		AppEngineConstants(const AppEngineConstants& rhs);
		~AppEngineConstants() = default;

	public:
		static const int CameraViewportWidth = 640;
		static const int CameraViewportHeight = 480;
		static const bool DemoMode = false;
	};
}
