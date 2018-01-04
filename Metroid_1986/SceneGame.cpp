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


}
void SceneGame::LoadObject(){
	//_player = new Player(650,2390);
	_player = new Player(2700, 7200);
	//// player in begin is centered on screen
	if (_player->getDirectionOfFace()==DirectionOfFace::Neutral)//begin, player has direction = neutral
		_camera->_viewport.x = _player->_posX - _screenWidth / 2;
	//_camera->_viewport.y = 2560;


	//other object

}

void SceneGame::RenderFrame(int time){
	//after 1 time = 4s then allow player control by keyboard
	DWORD timeNow = GetTickCount();
	if (timeNow - _stageStartTime <= 0000) //4000
	{
		_player->BeWounded(Direction::None_Direction, 0);
		//_player->_isMotionless = true;
	}
		
	//else if (timeNow - _stageStartTime <= 4100)
	//{
	//	_player->removeAction(BeWounded);
	//	_player->_isMotionless = false;
	//}


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
	_camera->UpdateCamera(_player->_posX, _player->_posY);

	
	//Infor::draw(_player->getHP());
	//UPDATE MAPS
	_tileGrid->Update(_camera,time);

	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1000))
	//{
	//	Zoomer* zoomer = new Zoomer(696, 2520,2);
	//	currentObjects->insert(pair<int, GameObject*>(1000, zoomer));
	//}

	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1001))
	//{
	//	Ripper* ripper = new Ripper(660, 2460, 1);
	//	currentObjects->insert(pair<int, GameObject*>(1001, ripper));

	//}
	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1002))
	//{
	//	Zeb* zeb = new Zeb(660, 2400, 2);
	//	currentObjects->insert(pair<int, GameObject*>(1002, zeb));

	//}
	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1003))
	//{
	//	Skree* skree = new Skree(750, 2400,2);
	//	currentObjects->insert(pair<int, GameObject*>(1003, skree));
	//}

	/*map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	if (!currentObjects->count(1004))
	{
		Waver* waver = new Waver(750, 2340, 1);
		currentObjects->insert(pair<int, GameObject*>(1004, waver));
	}*/

	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1005))
	//{
	//	Rio* rio = new Rio(800, 2500, 1);
	//	currentObjects->insert(pair<int, GameObject*>(1005, rio));
	//}
	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1006))
	//{
	//	ZebProductionPipe* zebpipe = new ZebProductionPipe(696, 2370, 2);
	//	currentObjects->insert(pair<int, GameObject*>(1006, zebpipe));
	//}

	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1007))
	//{
	//	Ridley* ridley = new Ridley(784, 2372);
	//	currentObjects->insert(pair<int, GameObject*>(1007, ridley));
	//}

	/*map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	if (!currentObjects->count(1008))
	{
		Kraid* kraid = new Kraid(784, 2450);
		currentObjects->insert(pair<int, GameObject*>(1008, kraid));
	}*/
	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//if (!currentObjects->count(1009))
	//{
	//	LongBeam* longbeam = new LongBeam(784, 2450);
	//	currentObjects->insert(pair<int, GameObject*>(1009, longbeam));
	//}
	//map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	//IceBeam* icebeam = new IceBeam(784, 2400);
	//currentObjects->insert(pair<int, GameObject*>(1010, icebeam));

	//WaveBeam* waveBeam = new WaveBeam(800, 2400);
	//currentObjects->insert(pair<int, GameObject*>(1011, waveBeam));

	//MissibleRocket* missibleRocket = new MissibleRocket(820, 2400);
	//currentObjects->insert(pair<int, GameObject*>(1012, missibleRocket));


	map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	if (!currentObjects->count(1013))
	{
		Rocket* rocket = new Rocket(784, 2450);
		currentObjects->insert(pair<int, GameObject*>(1013, rocket));
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
	Infor::draw(_player->getHP(),_player->getRocketNumber());
	G_SpriteHandler->End();
}

void SceneGame::handleCollision(int dt){
	//D3DXVECTOR2 playerPosition = D3DXVECTOR2{ _player->_posX, _player->_posY };
	_tileGrid->handleCollision(_player->_posX, _player->_posY, dt);

	_player->handleCollision(*_tileGrid->getCurrentObjects(),dt);
};

void SceneGame::KeyPress(int KeyCode){
	
	//if (_player->_isMotionless)		//don't allow press or release keys
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