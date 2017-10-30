#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include "Global Setting.h"


class Texture{
	char* _filePath; 
	RECT _size;		
	LPDIRECT3DTEXTURE9 _texture;
	int _cols;		
	int _rows;			
	int _frameWidth;		
	int _frameHeight;	
	void LoadTexture();
public:
	Texture();
	Texture(char* fileName, int cols = 1, int rows = 1);
	~Texture();
	void Draw(int x, int y);
};

#endif TEXTURE_H
