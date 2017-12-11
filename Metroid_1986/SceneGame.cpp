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
	_tileGrid = TileGrid::getInstance();
	//create player + other object
	LoadObject();
	//playerTexture = new Texture("Resources/Image/playerdemo.png", 4, 1);
	

	//Time in Stage
	_stageStartTime = GetTickCount();


}
void SceneGame::LoadObject(){
	_player = new Player(640,1100);

	_camera->SetSizeMap(0, 1280);
	//// player in begin is centered on screen
	if (_player->getDirectionOfMotion()==DirectionOfMotion::Neutral)//begin, player has direction = neutral
		_camera->_viewport.x = _player->_posX - _screenWidth / 2;
	_camera->_viewport.y = 1280;


	//other object

}

void SceneGame::RenderFrame(int time){
	//after 1 time = 4s then allow player control by keyboard
	DWORD timeNow = GetTickCount();
	if (timeNow - _stageStartTime <= 1000) //4000
		_player->_isStop = true;
	else
		_player->_isStop = false;

	//draw black background
	G_d3ddv->StretchRect(
		_background,			// from 
		NULL,				// which portion?
		G_backBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);

	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	_camera->UpdateCamera(_player->_posX);

	//draw background(ground)
	_backgroundMap->Draw(_camera);
	
	//UPDATE POSITION
	_tileGrid->Update(_camera,time);
	_player->Update(time);

	//COLLISION
	handleCollision(time);

	//UPDATE STATUS, ACTION AND FRAMES ANIMATION AFTER COLLISION
	_tileGrid->Update2(time);
	_player->Update2(time);

	//DRAW
	_tileGrid->Draw(_camera);
	_player->Draw(_camera);

	G_SpriteHandler->End();
}

void SceneGame::handleCollision(int dt){
	_tileGrid->handleCollision(dt);

	_player->handleCollision(*_tileGrid->getCurrentObjects(),dt);
};
//TileGrid* SceneGame::getTileGrid(){
//	return _tileGrid;
//}
void SceneGame::KeyPress(int KeyCode){
	
	//if (_player->_isStop)		//don't allow press or release keys
	//	return;


	ActionKey actionKey;
	switch (KeyCode)
	{
	case DIK_RIGHT:
		actionKey = Right_Key;
		break;
	case DIK_LEFT:
		actionKey = Left_Key;
		break;
	case DIK_UP:
		actionKey = Up_Key;
		break;
	case DIK_DOWN:
		actionKey = Down_Key;
		break;
	case DIK_F:
		actionKey = Jump_Key;
		break;
	case DIK_D:
		actionKey = Shoot_Key;
		break;
	default:
		return;
	}
	_player->_currentKeys = ActionKey(_player->_currentKeys | actionKey);
}
void SceneGame::KeyRelease(int KeyCode){
	ActionKey actionKey;
	switch (KeyCode)
	{
	case DIK_RIGHT:
		actionKey = Right_Key;
		break;
	case DIK_LEFT:
		actionKey = Left_Key;
		break;
	case DIK_UP:
		actionKey = Up_Key;
		break;
	case DIK_DOWN:
		actionKey = Down_Key;
		break;
	case DIK_F:
		actionKey = Jump_Key;
		break;
	case DIK_D:
		actionKey = Shoot_Key;
		break;
	default:
		return;
	}

	if (_player->isHasKey(actionKey))	//has actionkey
	_player->_currentKeys = ActionKey(_player->_currentKeys &~actionKey);	//remove
}