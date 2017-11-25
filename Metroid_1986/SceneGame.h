#ifndef _SCENEGAME_H
#define _SCENEGAME_H

#pragma once
#include "Scene.h"
#include "Player.h"
#include "Game.h"
#include "BackgroundMap.h"
#include "TileGrid.h"
#include "Texture2.h"


class SceneGame : public Scene{
	DWORD _stageStartTime;
	int _currentLevel;

	BackgroundMap* _backgroundMap;
	TileGrid* _tileGrid;
	Camera* _camera;
	Player* _player;



	void LoadObject(); //Load all object of current level
public :
	SceneGame();
	~SceneGame();
	void LoadResources();
	void RenderFrame(int t);


	void KeyPress(int KeyCode);
	void KeyRelease(int KeyCode);//stop current action
};
#endif _SCENEGAME_H