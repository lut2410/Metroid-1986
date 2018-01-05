#ifndef _SCENEEND_H
#define _SCENEEND_H

#pragma once
#include "Scene.h"
#define CHOOSEICON_FILE "Resources/Image/ChooseIcon.png"
#define COLOR_MENU D3DCOLOR_ARGB(255, 172, 231, 255)
class SceneEnd : public Scene{
	Texture2* _chooseIcon;
	DWORD _localTime;
	Font* _font;
	char** _menuChoice;
	int _currentChoice;
	void _openChoice();	//slect a option => open
public:
	SceneEnd();
	void RenderFrame(int t);
	void LoadResources();
	void KeyPress(int KeyCode);	//up-down key => change
	~SceneEnd();
};
#endif _SCENEEND_H