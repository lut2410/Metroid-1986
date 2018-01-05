#include "SceneMain.h"
SceneMain* SceneMain::_instance = NULL;
SceneMain::SceneMain(){
		_currentScene = new SceneMenu();
		_currentStateScene = ESceneState::Scene_Menu;
};
//SceneMain::SceneMain(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound) : Game( hInstance, name, mode, frameRate, isFullscreen, backgroundSound, effectSound)
//{
//	_currentScene = new SceneMenu();
//	_currentStateScene = ESceneState::Scene_Menu;
//
//}
//SceneMain::SceneMain(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound) : Game(hInstance, name, mode, frameRate, isFullscreen, backgroundSound, effectSound)
//{
//	_currentScene = new SceneMenu();
//	_currentStateScene = ESceneState::Scene_Menu;
//
//}

SceneMain* SceneMain::getInstance(){
	if (!_instance)
		_instance = new SceneMain();

	return _instance;
};
Scene* SceneMain::getCurrentScene(){
	return _currentScene;
};
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
		case ESceneState::Scene_End:
			_currentScene = new SceneEnd();
			_currentScene->LoadResources();
			break;

		}
		//change flag to match with _currentScene
		_currentStateScene = _currentScene->getSceneState();
	}
	_currentScene->RenderFrame(t);
}


void SceneMain::LoadResources()
{
	_currentScene->LoadResources();
}

//TileGrid* SceneMain::getTileGrid(){
//	return _currentScene->getTileGrid();
//	
//};
void SceneMain::KeyPress(int KeyCode)
{
	_currentScene->KeyPress(KeyCode);
}
void SceneMain::KeyRelease(int KeyCode)
{
	/*std::string key = std::to_string(KeyCode);
	char const* k = key.c_str();
	MessageBox(G_hWnd, "Realease", k, MB_OK);*/

	_currentScene->KeyRelease(KeyCode);
}

SceneMain::~SceneMain(void)
{
}