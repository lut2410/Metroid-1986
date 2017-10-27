#ifndef _SCENE_H
#define _SCENE_H

#pragma once
#include <time.h>
#include <d3d9.h>
#include "Font.h"

static enum ESceneState
{
	Scene_Menu,
	Scene_Intro,
	Scene_Game,
	Scene_End
} EnumSceneState; 

//load Surface from file
LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, char* filePath);


class Scene{
protected:
	LPDIRECT3DSURFACE9 _background;
	//Camera* _camera;
	ESceneState _sceneState;

public:
	Scene(ESceneState);
	ESceneState getSceneState();
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(int keyCode);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);

	~Scene(void);
};
#endif