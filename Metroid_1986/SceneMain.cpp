#include "SceneMain.h"
SceneMain::SceneMain(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound) : Game( hInstance, name, mode, frameRate, isFullscreen, backgroundSound, effectSound)
{
	_sceneNow = new SceneMenu();
	_currentStateScene = ESceneState::Scene_Menu;

}
SceneMain::SceneMain(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound) : Game(hInstance, name, mode, frameRate, isFullscreen, backgroundSound, effectSound)
{
	_sceneNow = new SceneMenu();
	_currentStateScene = ESceneState::Scene_Menu;

}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t){
	if (_sceneNow->getSceneState() != _currentStateScene)
	{
		switch (_sceneNow->getSceneState())
		{

		case ESceneState::Scene_Menu:
			_sceneNow = new SceneMenu();
			_sceneNow->LoadResources(d3ddv);
			break;
	/*	case ESceneState::Scene_Game:
			_sceneNow = new SceneGame();
			_sceneNow->LoadResources(d3ddv);
			break;
		case ESceneState::Scene_End:
			_sceneNow = new SceneEndGame();
			_sceneNow->LoadResources(d3ddv);
			break;*/

		}
		//change flag to match with _sceneNow
		_currentStateScene = _sceneNow->getSceneState();
	}
	_sceneNow->RenderFrame(d3ddv, t);
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	_sceneNow->LoadResources(d3ddv);
}

void SceneMain::OnKeyDown(int KeyCode)
{
	_sceneNow->OnKeyDown(KeyCode);
}

SceneMain::~SceneMain(void)
{
}