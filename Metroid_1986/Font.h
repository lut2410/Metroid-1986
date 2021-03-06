#ifndef FONT_H
#define FONT_H

#include <iostream>
#include "Global Setting.h"
using namespace std;

#define FRAME_RATE 20

class Font
{
private:
	LPD3DXFONT	_font;
	RECT		_fontPosition;
	DWORD _localTime;
	int _frameRate;			//just for font
	bool _isDrawAnimation;	//for render twinkling


public:
	Font(int size);
	~Font();
	void render(char* text_, float x_, float y_, D3DCOLOR color_ = D3DCOLOR_ARGB(255, 255, 255, 255));
	void render(int number_, float x_, float y_, D3DCOLOR color_ = D3DCOLOR_ARGB(255, 255, 255, 255));
	void renderFlicker(char* text_, float x_, float y_, int deltaTime_);
	void renderFlicker(int number_, float x_, float y_, int deltaTime_);
	void onLost();
};
#endif