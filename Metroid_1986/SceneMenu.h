#ifndef _SCENEMENU_H
#define _SCENEMENU_H

#pragma once
#include "Scene.h"

#define CHOOSEICON_FILE "Resources/Image/ChooseIcon.png"
#define INTRO_BACKGROUND_FILE	"Resources/Image/Scene Background/intro_background.jpg"
#define COLOR_MENU D3DCOLOR_ARGB(255, 172, 231, 255)

class SceneMenu : public Scene{
protected:
	Texture2* _chooseIcon;
	DWORD _localTime;
	Font* _font;
	char** _menuChoice;
	int _currentChoice;
	void _openChoice();	//slect a option => open
public:
	SceneMenu();
	void RenderFrame( int t);
	void LoadResources();
	void KeyPress(int KeyCode);	//up-down key => change
	~SceneMenu();
};
#endif _SCENEMENU_H