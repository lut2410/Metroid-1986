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
	Infor();
	//playerTexture = new Texture("Resources/Image/playerdemo.png", 4, 1);
	

	//Time in Stage
	_stageStartTime = GetTickCount();

	GameSound* s = GameSound::getInstance();
	s->stop(SOUND_INTRO_SCENE);
	s->stop(SOUND_END_SCENE);
	s->play(SOUND_PLAY_SCENE,true);
}
void SceneGame::LoadObject(){
	_player = new Player(650, 4450);
	//_player = new Player(2609, 4475);	//icebeam
	//_player = new Player(3900, 7050);	//pipe
	//_player = new Player(2683, 6586);	//rio
	//_player = new Player(2691, 5780);	//boss:ridley
	//_player = new Player(2635, 4956);	//boss:kraid
	//// player in begin is centered on screen
	if (_player->getDirectionOfFace()==DirectionOfFace::Neutral)//begin, player has direction = neutral
		_camera->_viewport.x = _player->_posX - _screenWidth / 2;
	//if (_player->getDirectionOfFace() == DirectionOfFace::Neutral)//begin, player has direction = neutral
	//	_camera->_viewport.y = _player->_posY - _screenHeight / 2;


	//other object

}

void SceneGame::RenderFrame(int time){
	CheckEndGame();
	//after 1 time = 4s then allow player control by keyboard
	DWORD timeNow = GetTickCount();
	if (timeNow - _stageStartTime <= 4000) //4000
	{
		_player->BeWounded(Direction::None_Direction, 0);
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

	/*	_tileGrid->Update(_camera, time);*/
		_tileGrid->Draw(_camera);
		G_SpriteHandler->End();
		return;
	}
	_player->UpdatePostionToInsideCamera();
	_camera->UpdateCamera(_player->_posX, _player->_posY);

	
	//Infor::draw(_player->getHP());
	//UPDATE MAPS
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
	//draw background(ground)
	_backgroundMap->Draw(_camera);
	//Infor: HP of player
	Infor::draw(_player->getHP(),_player->getRocketNumber());
	G_SpriteHandler->End();
}

void SceneGame::handleCollision(int dt){
	//D3DXVECTOR2 playerPosition = D3DXVECTOR2{ _player->_posX, _player->_posY };
	_tileGrid->handleCollision(_player->_posX, _player->_posY, dt);

	_player->handleCollision(*_tileGrid->getCurrentObjects(),dt);
};
void SceneGame::CheckEndGame()
{
	if (_player->getObjectStatus()==ObjectStatus::Died_OS)
		_sceneState = Scene_GameOver;
}
void SceneGame::KeyPress(int KeyCode){
	
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
	case DIK_SPACE:
		//switch bullet type
		_player->SwitchToOtherBulletType();
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