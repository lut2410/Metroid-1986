#include "Global Setting.h"

//char*		Glb_GameName =		"Metroid"; //Caption
//int			Glb_ScreenMode =	GAME_SCREEN_RESOLUTION_800_600_24;
//int			Glb_FrameRate =		60;
//bool		Glb_IsFullScreen=	false;
//bool		Glb_BackgroundSound=true;
//bool		Glb_EffectSound=	true;

HINSTANCE				G_hInstance;
HWND						G_hWnd;
//LPCSTR					_name;
CHAR* _name;

LPDIRECTINPUT8			G_DirectInput;
LPDIRECTINPUTDEVICE8		G_KeyBoard;
LPD3DXSPRITE				G_SpriteHandler;

LPDIRECT3D9				G_d3d = NULL;
LPDIRECT3DDEVICE9		G_d3ddv = NULL;
LPDIRECT3DSURFACE9		G_backBuffer = NULL;
D3DFORMAT				G_backBufferFormat = D3DFMT_X8R8G8B8;

int _screenWidth;
int _screenHeight;
int _depth;
bool _keyboardWorking = true;