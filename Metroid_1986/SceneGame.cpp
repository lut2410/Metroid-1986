#include "SceneGame.h"
SceneGame::SceneGame():Scene(Scene_Game){
	_currentLevel = 1;
}
SceneGame::~SceneGame(){}
void SceneGame::LoadResources() {
	srand((unsigned)time(NULL));

	D3DXCreateSprite(G_d3ddv, &G_SpriteHandler);

	_background = CreateSurfaceFromFile(G_d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(G_d3ddv, &G_SpriteHandler);


	//Load maps

	//create player + other object
	LoadObject();
	//playerTexture = new Texture("Resources/Image/playerdemo.png", 4, 1);


}
void SceneGame::LoadObject(){
	_player = new Player(300, 300);

	//other object

}

void SceneGame::RenderFrame(int time){

	//draw black background
	G_d3ddv->StretchRect(
		_background,			// from 
		NULL,				// which portion?
		G_backBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);


	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//draw maps
	//draw player
	//playerTexture->Draw(300, 300);
	_player->Update(time);
	_player->Draw();
	G_SpriteHandler->End();
}

void SceneGame::OnKeyDown(int KeyCode){

}