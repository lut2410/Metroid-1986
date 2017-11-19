#ifndef TEXTURE2_H
#define TEXTURE2_H

#pragma once
#include "Global Setting.h"
#include "AABB.h"

using namespace std;
class Texture2{
	friend class Sprite;
	LPDIRECT3DTEXTURE9 _texture;
	RECT _size;
	int _frameCount;
	vector<Box>* _framePosition;		//position of frame in texture
	void _LoadTexture(char*);
	void _ImportFromTextFile(char*);
public:
	Texture2(const Texture2 &texture);
	//Texture2(char* , int = 1, int = 1);
	Texture2(char*, char* = NULL);
	~Texture2();
	void Draw(int,int);
};
#endif