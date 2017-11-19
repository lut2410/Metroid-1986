#include "SceneGame.h"
SceneGame::SceneGame():Scene(Scene_Game){
	_camera= new Camera();
	_currentLevel = 1;
}
SceneGame::~SceneGame(){}
void SceneGame::LoadResources() {
	srand((unsigned)time(NULL));

	D3DXCreateSprite(G_d3ddv, &G_SpriteHandler);

	_background = CreateSurfaceFromFile(G_d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(G_d3ddv, &G_SpriteHandler);


	//Load maps
	_backgroundMap = new BackgroundMap();
	_tileGrid = new TileGrid();
	//create player + other object
	LoadObject();
	//playerTexture = new Texture("Resources/Image/playerdemo.png", 4, 1);
	

	//Time in Stage
	_stageStartTime = GetTickCount();


}
void SceneGame::LoadObject(){
	_player = new Player(600, 16);

	_camera->SetSizeMap(0, 1280);
	//// player in begin is centered on screen
	if (_player->getDirectionOfMotion()==DirectionOfMotion::Neutral)//begin, player has direction = neutral
		_camera->_viewport.x = _player->_posX - _screenWidth / 2;
	_camera->_viewport.y = 240;


	//other object

}

void SceneGame::RenderFrame(int time){
	//after 1 time = 4s then allow player control by keyboard
	DWORD timeNow = GetTickCount();
	if (timeNow - _stageStartTime <= 1000) //4000
		_keyboardWorking = false;
	else
		_keyboardWorking = true;

	//draw black background
	G_d3ddv->StretchRect(
		_background,			// from 
		NULL,				// which portion?
		G_backBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);

	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	_camera->UpdateCamera(_player->_posX);

	//draw maps
	_backgroundMap->Draw(_camera);
	//draw object
	_tileGrid->GetCurrentTileIDs(_camera->_viewport.x, _camera->_viewport.y);

	//draw player
	_player->Update(time);
	// collision
	_player->Draw(_camera);
	G_SpriteHandler->End();
}

void SceneGame::KeyPress(int KeyCode){
	
	switch (KeyCode)
	{
	case DIK_RIGHT:
		_player->SpecifyDirectionOfMotion_KeyPress(KeyCode);
		break;
	case DIK_LEFT:
		_player->SpecifyDirectionOfMotion_KeyPress(KeyCode);
		break;
	case DIK_UP:
		_player->SpecifyHavingPutHandUp_KeyPress();
		break;
	case DIK_DOWN:
		_player->SpecifyFootAction_KeyPress(KeyCode);
		break;
	case DIK_F://jump
		_player->SpecifyFootAction_KeyPress(KeyCode);
		break;



	}
}
void SceneGame::KeyRelease(int KeyCode){

	switch (KeyCode)
	{
	case DIK_RIGHT:
		_player->SpecifyDirectionOfMotion_KeyRelease(KeyCode);
		break;
	case DIK_LEFT:
		_player->SpecifyDirectionOfMotion_KeyRelease(KeyCode);
		break;
	case DIK_UP:
		_player->SpecifyHavingPutHandUp_KeyRelease();
		break;
	case DIK_DOWN:
		_player->SpecifyFootAction_KeyRelease(KeyCode);
		break;
	case DIK_F://jump
		_player->SpecifyFootAction_KeyRelease(KeyCode);
		break;
	}
}