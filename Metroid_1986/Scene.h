#ifndef _SCENE_H
#define _SCENE_H

#pragma once
#include "Global Setting.h"
#include "Font.h"
#include "Texture.h"
#define BACKGROUND_FILE "Resources/Image/black.png"
static enum ESceneState
{
	Scene_Menu,
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
	virtual void RenderFrame( int t);
	virtual void ProcessInput(int keyCode);
	virtual void LoadResources();
	virtual void OnKeyDown(int KeyCode);

	~Scene(void);
};
#endif