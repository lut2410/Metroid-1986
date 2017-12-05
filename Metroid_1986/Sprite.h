#ifndef SPRITE_H
#define SPRITE_H

#pragma once
#include "Texture2.h"
class Sprite {

protected:
	Texture2* _texture2;
	int _index;
	
public:
	Sprite();
	Sprite(Texture2* texture, int index);
	
	//Render current sprite in location(x,y) at the target surface
	void Draw(int x, int y);						//Draw sprite
	void DrawFlipHorizontal(int x, int y);			//Draw sprite flip horizontal
	Box	getSpriteSize();						//size of sprite
	~Sprite();
};
#endif SPRITE_H