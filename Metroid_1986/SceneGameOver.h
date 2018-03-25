#ifndef _SceneGameOver_H
#define _SceneGameOver_H

#pragma once
#include "Scene.h"
#define CHOOSEICON_FILE "Resources/Image/ChooseIcon.png"
#define VICTORY_BACKGROUND_FILE "Resources/Image/Scene Background/victory.png"
#define GAMEOVER_BACKGROUND_FILE "Resources/Image/Scene Background/gameover.jpg"
#define COLOR_MENU D3DCOLOR_ARGB(255, 23, 40, 47)
class SceneGameOver : public Scene{
	Texture2* _chooseIcon;
	DWORD _localTime;
	Font* _font;
	char** _menuChoice;
	int _currentChoice;
	void _openChoice();	//slect a option => open
public:
	SceneGameOver();
	void RenderFrame(int t);
	void LoadResources();
	void KeyPress(int KeyCode);	//up-down key => change
	~SceneGameOver();
};
#endif _SceneGameOver_H