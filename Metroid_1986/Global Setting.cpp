#include "Global Setting.h"

//char*		Glb_GameName =		"Metroid"; //Caption
//int			Glb_ScreenMode =	GAME_SCREEN_RESOLUTION_800_600_24;
//int			Glb_FrameRate =		60;
//bool		Glb_IsFullScreen=	false;
//bool		Glb_BackgroundSound=true;
//bool		Glb_EffectSound=	true;

HINSTANCE				_hInstance;
HWND						_hWnd;
//LPCSTR					_name;
CHAR* _name;

LPDIRECTINPUT8			G_DirectInput;
LPDIRECTINPUTDEVICE8		G_KeyBoard;
LPD3DXSPRITE				G_SpriteHandler;

LPDIRECT3D9				_d3d = NULL;
LPDIRECT3DDEVICE9		_d3ddv = NULL;
LPDIRECT3DSURFACE9		_backBuffer = NULL;
D3DFORMAT				_backBufferFormat = D3DFMT_X8R8G8B8;

int _screenWidth;
int _screenHeight;
int _depth;