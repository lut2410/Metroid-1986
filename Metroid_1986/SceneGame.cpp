#include "SceneGame.h"
SceneGame::SceneGame():Scene(Scene_Game){
	_camera= Camera::getInstance();
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
	_player = new Player(650,2450);

	//// player in begin is centered on screen
	if (_player->getDirectionOfMotion()==DirectionOfMotion::Neutral)//begin, player has direction = neutral
		_camera->_viewport.x = _player->_posX - _screenWidth / 2;
	_camera->_viewport.y = 2560;


	//other object

}

void SceneGame::RenderFrame(int time){
	//after 1 time = 4s then allow player control by keyboard
	DWORD timeNow = GetTickCount();
	if (timeNow - _stageStartTime <= 4000) //4000
	{
		_player->addOrChangeAction(BeWounded);
		_player->_isMotionless = true;
	}
		
	else if (timeNow - _stageStartTime <= 4100)
	{
		_player->removeAction(BeWounded);
		_player->_isMotionless = false;
	}


	//draw black background
	G_d3ddv->StretchRect(
		_background,			// from 
		NULL,				// which portion?
		G_backBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);

	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	if (_camera->_directionOfTheGate)
	{
		_camera->passTheGate();
		_backgroundMap->Draw(_camera);

		_tileGrid->Update(_camera, time);
		_tileGrid->Draw(_camera);
		G_SpriteHandler->End();
		return;
	}
	_player->UpdatePostionToInsideCamera();
	_camera->UpdateCamera(_player->_posX);

	
	//Infor::draw(_player->getHP());
	//UPDATE MAPS
	_tileGrid->Update(_camera,time);
	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1000))
	//{
	//	Zoomer* zoomer = new Zoomer(578, 1079,2);
	//	currentObjects->insert(pair<int, GameObject*>(300, zoomer));

	//}
	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1001))
	//{
	//	Ripper* ripper = new Ripper(660, 2490, 1);
	//	currentObjects->insert(pair<int, GameObject*>(1001, ripper));

	//}
	map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	if (!currentObjects->count(1002))
	{
		Zeb* zeb = new Zeb(660, 2400, 1);
		currentObjects->insert(pair<int, GameObject*>(1002, zeb));

	}
	_player->Update(time);

	//COLLISION
	handleCollision(time);

	//UPDATE STATUS, ACTION AND FRAMES ANIMATION AFTER COLLISION
	_tileGrid->Update2(time);
	_player->Update2(time);

	//DRAW
	_tileGrid->Draw(_camera);
	_player->Draw(_camera);
	//draw background(ground)
	_backgroundMap->Draw(_camera);
	//Infor: HP of player
	Infor::draw(_player->getHP());
	G_SpriteHandler->End();
}

void SceneGame::handleCollision(int dt){
	//D3DXVECTOR2 playerPosition = D3DXVECTOR2{ _player->_posX, _player->_posY };
	_tileGrid->handleCollision(_player->_posX, _player->_posY, dt);

	_player->handleCollision(*_tileGrid->getCurrentObjects(),dt);
};

void SceneGame::KeyPress(int KeyCode){
	
	if (_player->_isMotionless)		//don't allow press or release keys
		return;


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