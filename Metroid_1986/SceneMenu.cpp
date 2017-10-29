#include "SceneMenu.h"
#include "Global Setting.h"

SceneMenu::SceneMenu() :Scene(Scene_Menu){
	_localTime = 0;
	_currentChoice = 0;
	_menuChoice = (char**)malloc(2 * sizeof(char*));
	_menuChoice[0] = "START";
	_menuChoice[1] = "CONTINUE";

}

void SceneMenu::_openChoice(){
	MessageBox(G_hWnd, "Da Chon", "ThongBao", MB_OK);
}
void SceneMenu::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->StretchRect(
		_background,			// from 
		NULL,				// which portion?
		G_backBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);

	
	//this->_draw();
	//draw Option Select
	_font->render(_menuChoice[0], 380, 280, COLOR_MENU);
	_font->render(_menuChoice[1], 380, 320, COLOR_MENU);
	RECT* rct = new RECT;
	switch (_currentChoice)
	{
	case 0:
		 rct = new RECT{ 360, 280, 380, 300 };
		break;
	case 1:
		 rct = new RECT{ 360, 320, 380, 340 };
		break;
	default:
		break;
	}

	// draw chooseIcon
	d3ddv->StretchRect(
		_chooseIcon,			// from 
		NULL,				// which portion?
		G_backBuffer,		// to 
		rct,				// which portion?
		D3DTEXF_NONE);
}

void SceneMenu::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);


	_background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	_chooseIcon = CreateSurfaceFromFile(d3ddv, CHOOSEICON_FILE);
	 //res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	//D3DXVECTOR3 position((float)x, (float)y, 0);
	//G_SpriteHandler->Draw(Texture, &Size, NULL, &position, 0xFFFFFFFF);

	_font = new Font(d3ddv, 22);


	/*Sound::GetInst()->RemoveAllBGM();
	Sound::GetInst()->PlayBGSound(EBGSound::EMenuSound);*/
}

void SceneMenu::OnKeyDown(int KeyCode){
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