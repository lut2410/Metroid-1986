#pragma once
#include "Game.h"
#include "Scene.h"
#include "SceneMenu.h"
#include "SceneGame.h"
class SceneMain : public Game
{
protected:
	
	Scene* _currentScene;
	ESceneState _currentStateScene;

public:
	SceneMain(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	SceneMain(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	~SceneMain();
	//seems don't need virtual
	virtual void RenderFrame(int t);
	virtual void ProcessInput(int Delta);
	virtual void LoadResources();

	virtual void KeyPress(int KeyCode);
	virtual void KeyRelease(int KeyCode);
};