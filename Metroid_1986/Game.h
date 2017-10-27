#ifndef _GAME_H_
#define _GAME_H_

#include "Global Setting.h"
class  Game
{
protected:
	//LPDIRECT3D9 _d3d = NULL;    // the pointer to our Direct3D interface
	//LPDIRECT3DDEVICE9 _d3ddv = NULL;    // the pointer to the device class
	//LPDIRECT3DSURFACE9 _backBuffer = NULL;
	//D3DFORMAT _backBufferFormat = D3DFMT_X8R8G8B8;
			
	int _mode;				// Screen mode
	int _frameRate;
	bool _isFullScreen;		// Is running in fullscreen mode?
	bool _backgroundSound;
	bool _effectSound;

	//int _screenWidth;
	//int _screenHeight;
	//int _depth;

	//set mode Screen -> pecific screen width+height 
	void _SetScreenDimension();

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	void _InitWindow();
	void _InitKeyboard();
	void _InitDirectX();

	// Render a single frame
	void _RenderFrame(DWORD deltaTime);

	// Place holder for sub classes
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

public:
	Game(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	Game(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	~Game();

	int getMode();

	int getScreenWidth();
	int getScreenHeight();
	int getDepth();

	int frameRate;			// Desired frame rate of game

	// Initialize the game with set parameters
	void Init();

	// Run game
	void Run();

	BYTE  _KeyStates[256];

};

#endif _GAME_H