#pragma once
#include "SceneMain.h"


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	SceneMain g(hInstance, "Metroid 1986", ScreenResolution::Resolution_256_240_24, 60, false, true, true);
	g.Init();
	g.Run();
	return 0;
}
