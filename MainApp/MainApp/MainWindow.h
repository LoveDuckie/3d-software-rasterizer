#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;

namespace Framework
{
	class MainWindow
	{
	public:
		MainWindow();
		virtual ~MainWindow();

		// The static method that is called for when the window sends messages
		static LRESULT CALLBACK WndCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		bool Run(int CmdShow);
	
	private:
		HWND hWnd;
	};
};