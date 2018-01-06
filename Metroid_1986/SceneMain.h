#pragma once
#include "Game.h"
#include "Scene.h"
#include "SceneMenu.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
class SceneMain
{
protected:
	static SceneMain* _instance;
	Scene* _currentScene;


public:
	ESceneState _currentStateScene;
	static SceneMain* getInstance();
	Scene* getCurrentScene();
	SceneMain();
	//SceneMain(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	//SceneMain(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	~SceneMain();
	//seems don't need virtual
	virtual void RenderFrame(int t);
	virtual void LoadResources();

	//TileGrid* getTileGrid();
	virtual void KeyPress(int KeyCode);
	virtual void KeyRelease(int KeyCode);
};