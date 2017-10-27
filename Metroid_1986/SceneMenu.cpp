#include "SceneMenu.h"
#include "Global Setting.h"

SceneMenu::SceneMenu() :Scene(Scene_Menu){
	_localTime = 0;
	_currentSelection = 0;
	_menuOption = (char**)malloc(2 * sizeof(char*));
	_menuOption[0] = "START";
	_menuOption[1] = "CONTINUE";

}

void SceneMenu::_openOption(){
	
}
void SceneMenu::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->StretchRect(
		_background,			// from 
		NULL,				// which portion?
		_backBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	//this->_draw();
	//draw Option Select
	//_font->render(_menuOption[0], 220, 252);
	//_font->render(_menuOption[1], 215, 293);


}

void SceneMenu::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);


	_background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	_font = new Font(d3ddv, 22, _screenWidth, _screenHeight);

	/*Sound::GetInst()->RemoveAllBGM();
	Sound::GetInst()->PlayBGSound(EBGSound::EMenuSound);*/
}

void SceneMenu::OnKeyDown(int KeyCode){

};