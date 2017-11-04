#ifndef _GAME_H_
#define _GAME_H_

#include "Global Setting.h"

#define KEYBOARD_BUFFER_SIZE	1024
#define KEY_DOWN(vk_code) ( (_Keys[vk_code] & 0x80)? 1 : 0 )
class  Game
{
protected:
			
	int _mode;				// Screen mode
	int _frameRate;
	bool _isFullScreen;		// Is running in fullscreen mode?
	bool _backgroundSound;
	bool _effectSound;

	//set mode Screen -> pecific screen width+height 
	void _SetScreenDimension();

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void _InitWindow();
	void _InitKeyboard();
	void _InitDirectX();

	// Render a single frame
	void _RenderFrame(int deltaTime);

	// Place holder for sub classes
	virtual void RenderFrame(int Delta);
	virtual void LoadResources();
	void KeyboardHandling(); //process base Keyboard event
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
public:
	Game(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	Game(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound);
	~Game();

	int frameRate;			// Desired frame rate of game

	// Initialize the game with set parameters
	void Init();
	// Run game
	void Run();
	

	BYTE  _Keys[256];
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
};

#endif _GAME_H