#pragma once
#include "Scene.h"
#include "Font.h"

#define BACKGROUND_FILE "Resources/Image/black.png"
#define CHOOSEICON_FILE "Resources/Image/ChooseIcon.png"
#define COLOR_MENU D3DCOLOR_ARGB(255, 172, 231, 255)

class SceneMenu : public Scene{
protected:
	LPDIRECT3DSURFACE9 _chooseIcon;
	DWORD _localTime;
	Font* _font;
	char** _menuChoice;
	int _currentChoice;
	void _openChoice();	//slect a option => open
public:
	SceneMenu();
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void OnKeyDown(int KeyCode);	//up-down key => change
	~SceneMenu();

};