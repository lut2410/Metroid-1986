#ifndef _SCENEGAME_H
#define _SCENEGAME_H

#pragma once
#include "Scene.h"
#include "Player.h"
class SceneGame : public Scene{
	int _currentLevel;
	//Texture* playerTexture;
	Player* _player;
	//Object* o;
	void LoadObject(); //Load all object of current level
public :
	SceneGame();
	~SceneGame();
	void LoadResources();
	void RenderFrame(int t);
	void OnKeyDown(int KeyCode);
};
#endif _SCENEGAME_H