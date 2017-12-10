#ifndef TEXTURE2_H
#define TEXTURE2_H

#pragma once
#include "Global Setting.h"
#include "AABB.h"
#include <map>
using namespace std;
class Texture2{
	friend class Sprite;
public:
	LPDIRECT3DTEXTURE9 _texture;
	RECT _size;
	vector<Box>* _framePosition;							//position of frame in texture
	map<string, vector<int>>* _animationList; 				//list animation detail: name and 2 parameter type int -> frames of texture
	vector<string> _animationNames;
	void _LoadTexture(char*);
	void _ImportFromTextFile(char*);

	Texture2(const Texture2 &texture);
	Texture2(char*, char* = NULL);
	~Texture2();
	void Draw(int,int);										//Draw Texture
	void Draw(int x, int y, int index);						//Draw frame has specified index
};
#endif