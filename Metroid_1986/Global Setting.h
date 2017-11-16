#ifndef _GLOBAL_SETTING_H
#define _GLOBAL_SETTING_H
#pragma once
#include <windowsx.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <time.h>


#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2
#define GAME_SCREEN_RESOLUTION_256_240_24  3

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12

#define KEYBOARD_BUFFER_SIZE	1024

extern HINSTANCE				G_hInstance;	// Handle of the game instance
extern HWND						G_hWnd;				// Handle of the Game Window
//extern LPCSTR					_name;			// Name of game will be used as Window Class Name
extern char* _name;

extern LPDIRECTINPUT8			G_DirectInput;		// The DirectInput object         
extern LPDIRECTINPUTDEVICE8		G_KeyBoard;			// The keyboard device 
extern LPD3DXSPRITE				G_SpriteHandler;	// spriteHandler to draw texture

extern LPDIRECT3D9				G_d3d;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9		G_d3ddv;    // the pointer to the device class
extern LPDIRECT3DSURFACE9		G_backBuffer;
extern D3DFORMAT				G_backBufferFormat;

extern int _screenWidth;
extern int _screenHeight;
extern int _depth;
extern bool _keyboardWorking;	//allow keyboard? used for intro in each statge

//ID of Game Object
enum ObjectID{
	None_ID,
	Player_ID
};

#endif _GLOBAL_SETTING_H
