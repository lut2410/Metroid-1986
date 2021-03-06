#include "Scene.h"
Scene::Scene(ESceneState state){
	_background = NULL;
	//_camera = NULL;
	_sceneState = state;
};

ESceneState Scene::getSceneState()
{
	return _sceneState;
}

//TileGrid* Scene::getTileGrid(){
//	return NULL;	//not used
//};

void Scene::RenderFrame(int t)
{
}

void Scene::ProcessInput(int keycode)
{
}

void Scene::LoadResources()
{
}

void Scene::KeyPress(int KeyCode)
{
}
void Scene::KeyRelease(int KeyCode)
{
}
Scene::~Scene(void)
{
}

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, char* filePath)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile( filePath, &info);

	if (result != D3D_OK)
	{
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		 filePath,
		NULL,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		NULL);

	if (result != D3D_OK)
	{
		return NULL;
	}

	return surface;
}
