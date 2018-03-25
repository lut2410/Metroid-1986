#include "SceneGameOver.h"
#include "Global Setting.h"

SceneGameOver::SceneGameOver() :Scene(Scene_GameOver){
	_localTime = 0;
	_currentChoice = 0;
	_menuChoice = (char**)malloc(2 * sizeof(char*));
	_menuChoice[0] = "NEW GAME";
	_menuChoice[1] = "EXIT";

}

void SceneGameOver::_openChoice(){

	/*MessageBox(G_hWnd, "Da Chon", "ThongBao", MB_OK);*/
	switch (_currentChoice)
	{
	case 0:
		_sceneState = Scene_Game;
		break;
	case 1:
		PostMessage(G_hWnd, WM_QUIT, 0, 0);
		break;
	}
	
}
void SceneGameOver::RenderFrame(int t)
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

void SceneGameOver::LoadResources()
{
	srand((unsigned)time(NULL));

	_background = CreateSurfaceFromFile(G_d3ddv, GAMEOVER_BACKGROUND_FILE);

	_chooseIcon = new Texture2(CHOOSEICON_FILE);

	_font = new Font(10);

	GameSound* s = GameSound::getInstance();
	s->stop(SOUND_PLAY_SCENE);
	s->play(SOUND_END_SCENE, true);
}

void SceneGameOver::KeyPress(int KeyCode){
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