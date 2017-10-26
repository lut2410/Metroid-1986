#ifndef _GAME_H_
#define _GAME_H_
#include <windows.h>
#include <d3d9.h>

#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12

class  Game
{
protected:
	LPDIRECT3D9 _d3d = NULL;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 _d3ddv = NULL;    // the pointer to the device class
	LPDIRECT3DSURFACE9 _backBuffer = NULL;
	D3DFORMAT _backBufferFormat = D3DFMT_X8R8G8B8;

	int _mode;				// Screen mode 
	int _isFullScreen;		// Is running in fullscreen mode?
	int _frameRate;

	int _screenWidth;
	int _screenHeight;
	int _depth;

	HINSTANCE _hInstance;	// Handle of the game instance
	HWND _hWnd;				// Handle of the Game Window
	LPWSTR _name;			// Name of game will be used as Window Class Name



	void _SetScreenDimension(int mode);

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void _Init();
	void _InitWindow();
	void _InitDirectX();

	// Render a single frame
	void _RenderFrame(DWORD deltaTime);

	// Place holder for sub classes
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

public:
	Game(HINSTANCE hInstance, LPWSTR name, int mode, int isFullscreen, int frameRate);
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



};

#endif _GAME_H