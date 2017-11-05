#include "Game.h"
#include <string>
Game::Game(HINSTANCE hInstance, char* name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound){
	G_hInstance = hInstance;
	_name =  name;
	_mode = mode;
	_SetScreenDimension();
	_frameRate = frameRate;
	_isFullScreen = isFullscreen;
	_backgroundSound = backgroundSound;
	_effectSound = effectSound;
}

Game::Game(HINSTANCE hInstance, LPCWSTR name, int mode, int frameRate, bool isFullscreen, bool backgroundSound, bool effectSound){
	/*G_hInstance = hInstance;
	_name = name;
	_mode = mode;
	_SetScreenDimension();
	_frameRate = frameRate;
	_isFullScreen = isFullscreen;
	_backgroundSound = backgroundSound;
	_effectSound = effectSound;*/
}

Game::~Game(){
	if (G_d3ddv != NULL) G_d3ddv->Release();
	if (G_d3d != NULL) G_d3d->Release();

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
	wc.hInstance = G_hInstance;
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
	G_hWnd = CreateWindowEx(NULL, _name,    // name of the window class
		_name,   // title of the window
		style,    // window style  --- default: WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT,    // x & y position of the window
		_screenWidth,    // width of the window
		_screenHeight,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		G_hInstance,    // application handle
		NULL);    // used with multiple windows, NULL
	if (!G_hWnd)
	{
		DWORD ErrCode = GetLastError();
	}


	// display the window on the screen
	ShowWindow(G_hWnd, SW_SHOWNORMAL);
	UpdateWindow(G_hWnd);// need!
}
void Game::_InitDirectX(){
	G_d3d = Direct3DCreate9(D3D9b_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	if (G_d3d == NULL)
	{
		MessageBox(G_hWnd, "Error initializing Direct3D", "Error", MB_OK);
		//return 0;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = _isFullScreen ? FALSE : TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;// DISCARD OLD FRAMES -- BACKBUFFER
	d3dpp.BackBufferFormat = G_backBufferFormat; // then this is important
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = _screenWidth;
	d3dpp.BackBufferHeight = _screenHeight;
	d3dpp.hDeviceWindow = G_hWnd;

	G_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		G_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&G_d3ddv);
	if (G_d3ddv == NULL) {
		MessageBox(NULL, "Failed to create device", "Error", MB_OK);
		//return 0;
	}


	//G_d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0); //clear	backbuffer
	G_d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &G_backBuffer);
	D3DXCreateSprite(G_d3ddv, &G_SpriteHandler);
}
void Game::_InitKeyboard(){
	HRESULT
		result = DirectInput8Create
		(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&G_DirectInput, NULL
		);

	// TO-DO: put in exception handling
	if (result!= DI_OK)
		return;

	result = G_DirectInput->CreateDevice(GUID_SysKeyboard, &G_KeyBoard, NULL);

	// TO-DO: put in exception handling
	if (FAILED(result) == true)
		return;

	result = G_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result) == true)
		return;

	result = G_KeyBoard->SetCooperativeLevel(G_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result) == true)
		return;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	result = G_KeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(result) == true)
		return;

	result = G_KeyBoard->Acquire();
	if (FAILED(result) == true)
		return;
}
void Game::Init(){
	_InitWindow();
	_InitDirectX();
	_InitKeyboard();
	LoadResources();
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

		KeyboardHandling();

		// TO-DO: need to improve in later version
		if (KEY_DOWN(VK_ESCAPE)) PostMessage(G_hWnd, WM_QUIT, 0, 0);
	}

}
void Game::_RenderFrame(int deltaTime){
	if (G_d3ddv->BeginScene()) {
		RenderFrame(deltaTime);
		G_d3ddv->EndScene();
	}
	G_d3ddv->Present(NULL, NULL, NULL, NULL);

	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(G_hWnd, WM_DESTROY, 0, 0);
}
void Game::RenderFrame(int deltaTime) //int?DWORD
{
	G_d3ddv->ColorFill(G_backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
}
void Game::LoadResources(){

}


void Game::KeyboardHandling(){
	{
		if (_keyboardWorking == false)
		return;
		//poll the keyboardKEY_DOWN
		HRESULT hr = G_KeyBoard->GetDeviceState(sizeof(_Keys), (LPVOID)&_Keys);
		if (hr != S_OK)
		{
			hr = G_KeyBoard->Acquire();
			G_KeyBoard->GetDeviceState(sizeof(_Keys), (LPVOID)&_Keys);
		}
		// Collect all key states first
		G_KeyBoard->GetDeviceState(sizeof(_Keys), _Keys);

		if (KEY_DOWN(DIK_ESCAPE))
		{
			PostMessage(G_hWnd, WM_QUIT, 0, 0);
		}

		// Collect all buffered events
		DWORD dwElements = KEYBOARD_BUFFER_SIZE;
		hr = G_KeyBoard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

		// Scan through all data, check if the key is pressed or released
		for (DWORD i = 0; i < dwElements; i++)
		{
			int KeyCode = _KeyEvents[i].dwOfs;
			int KeyState = _KeyEvents[i].dwData;
			if ((KeyState & 0x80) > 0) // one key is pressed
				OnKeyDown(KeyCode);
			else
				// Key Up event
				OnKeyUp(KeyCode);
				;

		}
	}
}


void Game::OnKeyDown(int KeyCode){
};
void Game::OnKeyUp(int KeyCode){
};

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
