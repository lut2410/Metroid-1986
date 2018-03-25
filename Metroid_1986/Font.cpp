#include "font.h"


Font::Font(int size)
{
	_localTime = 0;
	_frameRate = FRAME_RATE;
	_isDrawAnimation = true;
	_fontPosition.top = 0;
	_fontPosition.left = 0;
	_fontPosition.right = _screenWidth;
	_fontPosition.bottom = _screenHeight;
	D3DXFONT_DESC FontDesc = {
		size,
		0,
		400,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE, "Arial"
};

	//create font
	D3DXCreateFontIndirect(G_d3ddv, &FontDesc, &_font);
}
Font::~Font()
{
	if (_font != NULL)
	{
		_font->Release(); //release font
		_font = NULL;
	}
}



void Font::render(char* text, float x, float y, D3DCOLOR color)
{
	_fontPosition.left = x;
	_fontPosition.top = y;

	_font->DrawText(NULL,
		text,
		-1,
		&_fontPosition,
		NULL,
		color); //draw text
}

void Font::render(int number_, float x_, float y_, D3DCOLOR color)
{
	render((char*)to_string(number_).c_str(), x_, y_, color);
}

void Font::renderFlicker(char* text_, float x_, float y_, int deltaTime_)
{
	_localTime += deltaTime_;
	if (_localTime >= 1000 / _frameRate)
	{
		_localTime = 0;
		//change flag
		_isDrawAnimation = !_isDrawAnimation;
	}

	if (this->_isDrawAnimation)
		render(text_, x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));

}
void Font::renderFlicker(int number_, float x_, float y_, int deltaTime_)
{
	_localTime += deltaTime_;
	if (_localTime >= 1000 / _frameRate)
	{
		render((char*)to_string(number_).c_str(), x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));
		_localTime = 0;
	}
}

void Font::onLost()
{
	_font->OnLostDevice();
	_font->OnResetDevice();
}
