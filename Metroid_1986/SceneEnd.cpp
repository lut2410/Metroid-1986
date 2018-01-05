#include "SceneEnd.h"
#include "Global Setting.h"

SceneEnd::SceneEnd() :Scene(Scene_End){
	_localTime = 0;
	_currentChoice = 0;
	_menuChoice = (char**)malloc(2 * sizeof(char*));
	_menuChoice[0] = "CONTINUE";
	_menuChoice[1] = "EXIT";

}

void SceneEnd::_openChoice(){

	/*MessageBox(G_hWnd, "Da Chon", "ThongBao", MB_OK);*/
	switch (_currentChoice)
	{
	case 0:
		_sceneState = Scene_Game;
		break;
	case 1:
		_sceneState = Scene_Menu;
		break;
	}
	
}
void SceneEnd::RenderFrame(int t)
{
	//Draw Backround & Font
	G_d3ddv->StretchRect(
		_background,			// from 
		NULL,				// which portion?
		G_backBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	_font->render(_menuChoice[0], _screenWidth / 2 - 10, _screenHeight / 2 - 10, COLOR_MENU);
	_font->render(_menuChoice[1], _screenWidth / 2 - 10, _screenHeight / 2, COLOR_MENU);

	//Draw Sprite
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (_currentChoice)
	{
	case 0:
		_chooseIcon->Draw(_screenWidth / 2 - 20, _screenHeight / 2 - 9);
		break;
	case 1:
		_chooseIcon->Draw(_screenWidth / 2 - 20, _screenHeight / 2 + 1);
		break;
	default:
		break;
	}
	G_SpriteHandler->End();

}

void SceneEnd::LoadResources()
{
	srand((unsigned)time(NULL));

	_background = CreateSurfaceFromFile(G_d3ddv, BACKGROUND_FILE);

	_chooseIcon = new Texture2(CHOOSEICON_FILE);

	_font = new Font(10);

	/*Sound::GetInst()->RemoveAllBGM();
	Sound::GetInst()->PlayBGSound(EBGSound::EMenuSound);*/
}

void SceneEnd::KeyPress(int KeyCode){
	switch (KeyCode)
	{
	case DIK_UP:

		_currentChoice = _currentChoice - 1;
		if (_currentChoice < 0) _currentChoice = 1;
		break;
	case DIK_DOWN:
		_currentChoice += 1;
		if (_currentChoice > 1) _currentChoice = 0;
		break;

	case DIK_RETURN:
		this->_openChoice();
		break;
	}
};