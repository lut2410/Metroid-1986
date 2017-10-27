#pragma once
#include "Scene.h"
#include "Font.h"

#define BACKGROUND_FILE "Resources/Image/black.png"

class SceneMenu : public Scene{
protected:
	DWORD _localTime;
	Font* _font;
	char** _menuOption;
	int _currentSelection;
	void _openOption();	//slect a option => open
public:
	SceneMenu();
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void OnKeyDown(int KeyCode);	//up-down key => change
	~SceneMenu();

};