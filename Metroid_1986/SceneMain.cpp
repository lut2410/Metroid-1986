#include "SceneMain.h"
SceneMain::SceneMain(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound) : Game( hInstance, name, mode, frameRate, isFullscreen, backgroundSound, effectSound)
{
	_currentScene = new SceneMenu();
	_currentStateScene = ESceneState::Scene_Menu;

}
SceneMain::SceneMain(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound) : Game(hInstance, name, mode, frameRate, isFullscreen, backgroundSound, effectSound)
{
	_currentScene = new SceneMenu();
	_currentStateScene = ESceneState::Scene_Menu;

}

void SceneMain::RenderFrame(int t){
	if (_currentScene->getSceneState() != _currentStateScene)
	{
		switch (_currentScene->getSceneState())
		{

		case ESceneState::Scene_Menu:
			_currentScene = new SceneMenu();
			_currentScene->LoadResources();
			break;
		case ESceneState::Scene_Game:
			_currentScene = new SceneGame();
			_currentScene->LoadResources();
			break;
		/*case ESceneState::Scene_End:
			_currentScene = new SceneEndGame();
			_currentScene->LoadResources();
			break;*/

		}
		//change flag to match with _currentScene
		_currentStateScene = _currentScene->getSceneState();
	}
	_currentScene->RenderFrame(t);
}

void SceneMain::ProcessInput(int Delta)
{
	
}

void SceneMain::LoadResources()
{
	_currentScene->LoadResources();
}

void SceneMain::OnKeyDown(int KeyCode)
{
	_currentScene->OnKeyDown(KeyCode);
}

SceneMain::~SceneMain(void)
{
}