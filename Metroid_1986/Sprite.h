#ifndef SPRITE_H
#define SPRITE_H

#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

class Sprite {
protected:
	LPDIRECT3DTEXTURE9 _Image;
	LPD3DXSPRITE _SpriteHandler;
	int _Index; //current sprite index
	int _Width; //sprite width
	int _Height; //sprite height
	int _Count; // Number of sprites in the container
	int _SpritePerRow; // Number of sprites per row
public:
	Sprite(LPD3DXSPRITE SpriteHandler, char* Path, int Width, int Height, int Count, int SpritePerRow);
	//next sprite in list
	void Next();
	//Render current sprite in location(x,y) at the target surface
	void Render(int x, int y);
	~Sprite();
};
#endif SPRITE_H