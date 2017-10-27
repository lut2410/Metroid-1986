#pragma once
#include "Game.h"
#include "Scene.h"
#include "SceneMenu.h"
class SceneMain : public Game
{
protected:
	
	Scene* _sceneNow;
	ESceneState _currentStateScene;

public:
	SceneMain(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	SceneMain(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	~SceneMain();
	//seems don't need virtual
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	virtual void OnKeyDown(int KeyCode);
	
};