#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Game.h"


#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0)

#define KEYBOARD_BUFFER_SIZE	1024



// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Game g(hInstance, L"Metroid 1986", GAME_SCREEN_RESOLUTION_800_600_24, 0, 24);
	g.Init();
	g.Run();
	return 0;
}
//int InitKeyboard(HINSTANCE hInstance, HWND hWnd){
//	HRESULT result;
//	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);
//	if (result != DI_OK)
//		return 0;
//
//	result = dinput->CreateDevice(GUID_SysKeyboard, &didev, NULL);
//	// keyboard or joystick ?
//	result = didev->SetDataFormat(&c_dfDIKeyboard);
//
//	result = didev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
//	
//
////COPY
//	DIPROPDWORD dipdw;
//
//	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
//	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
//	dipdw.diph.dwObj = 0;
//	dipdw.diph.dwHow = DIPH_DEVICE;
//	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size
//
//	//Buffersize keyboard
//	result = didev->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
//	if (result != DI_OK) return;
////END_COPY
//	result = didev->Acquire();
//
//	return 1;
//
//
//}