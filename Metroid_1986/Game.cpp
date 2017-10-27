#include "Game.h"
#include <string>
#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )
Game::Game(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound){
	_hInstance = hInstance;
	_name =  name;
	_mode = mode;
	_SetScreenDimension();
	_frameRate = frameRate;
	_isFullScreen = isFullscreen;
	_backgroundSound = backgroundSound;
	_effectSound = effectSound;
}

Game::Game(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound){
	/*_hInstance = hInstance;
	_name = name;
	_mode = mode;
	_SetScreenDimension();
	_frameRate = frameRate;
	_isFullScreen = isFullscreen;
	_backgroundSound = backgroundSound;
	_effectSound = effectSound;*/
}

Game::~Game(){
	if (_d3ddv != NULL) _d3ddv->Release();
	if (_d3d != NULL) _d3d->Release();

}
void Game::_SetScreenDimension(){
	switch (_mode){
	case GAME_SCREEN_RESOLUTION_640_480_24:
		_screenWidth = 640;
		_screenHeight = 480;
		_depth = 24;
		break;
	case GAME_SCREEN_RESOLUTION_800_600_24:
		_screenWidth = 800;
		_screenHeight = 600;
		_depth = 24;
		break;
	case GAME_SCREEN_RESOLUTION_1024_768_24:
		_screenWidth = 1024;
		_screenHeight = 768;
		_depth = 24;
		break;
	default:
		break;
	}
}
void Game::_InitWindow(){

	// this struct holds information for the window class
	WNDCLASSEX wc; // if charater set Property: Unicode ->WNDCLASSEXW
	// multi-byte -> WNDCLASSEXA ==>lpszClassName = _name Error
	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = _WinProc;
	wc.hInstance = _hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	//wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _name;

	// register the window class
	RegisterClassEx(&wc);

	// set full screen
	DWORD style;
	if (_isFullScreen) //full
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;


	// create the window and use the result as the handle
	_hWnd = CreateWindowEx(NULL, _name,    // name of the window class
		_name,   // title of the window
		style,    // window style  --- default: WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT,    // x & y position of the window
		_screenWidth,    // width of the window
		_screenHeight,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		_hInstance,    // application handle
		NULL);    // used with multiple windows, NULL
	if (!_hWnd)
	{
		DWORD ErrCode = GetLastError();
	}


	// display the window on the screen
	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);// need!
}
void Game::_InitDirectX(){
	_d3d = Direct3DCreate9(D3D9b_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	if (_d3d == NULL)
	{
		MessageBox(_hWnd, "Error initializing Direct3D", "Error", MB_OK);
		//return 0;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = _isFullScreen ? FALSE : TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;// DISCARD OLD FRAMES -- BACKBUFFER
	d3dpp.BackBufferFormat = _backBufferFormat; // then this is important
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = _screenWidth;
	d3dpp.BackBufferHeight = _screenHeight;
	d3dpp.hDeviceWindow = _hWnd;

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddv);
	if (_d3ddv == NULL) {
		MessageBox(NULL, "Failed to create device", "Error", MB_OK);
		//return 0;
	}


	//_d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0); //clear	backbuffer
	_d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_backBuffer);
}
void Game::_InitKeyboard(){
	HRESULT
		hr = DirectInput8Create
		(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&G_DirectInput, NULL
		);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return;

	hr = G_DirectInput->CreateDevice(GUID_SysKeyboard, &G_KeyBoard, NULL);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return;

	hr = G_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr) == true)
		return;

	hr = G_KeyBoard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr) == true)
		return;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = GL_KEY_BUFFER_SIZE;

	hr = G_KeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr) == true)
		return;

	hr = G_KeyBoard->Acquire();
	if (FAILED(hr) == true)
		return;
}
void Game::Init(){
	_InitWindow();
	_InitDirectX();
	_InitKeyboard();
	LoadResources(_d3ddv);
}
void Game::Run(){
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();
	DWORD cout_per_frame = 1000 / _frameRate;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DWORD deltaTime = now - frame_start;
		if (deltaTime >= cout_per_frame)
		{
			frame_start = now;
			_RenderFrame(deltaTime);
		}
		// TO-DO: need to improve in later version
		if (KEY_DOWN(VK_ESCAPE)) PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

}
void Game::_RenderFrame(DWORD deltaTime){
	if (_d3ddv->BeginScene()) {
		RenderFrame(_d3ddv, deltaTime);
		_d3ddv->EndScene();
	}
	_d3ddv->Present(NULL, NULL, NULL, NULL);

	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(_hWnd, WM_DESTROY, 0, 0);
}
void Game::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int deltaTime) //int?DWORD
{
	d3ddv->ColorFill(_backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
}
void Game::LoadResources(LPDIRECT3DDEVICE9 d3ddv){

}
// this is the main message handler for the program
LRESULT CALLBACK Game::_WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
		// close the application entirely
		PostQuitMessage(0);
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

}
