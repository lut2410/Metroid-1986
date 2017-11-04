#ifndef SPRITE_H
#define SPRITE_H

#pragma once
#include "Texture.h"

class Sprite {

protected:
	Texture* _texture;

	int _startIndex;		
	int _endIndex;		
	int _currentIndex;		
	int _timeAnimation;	
	int _timeLocal;	
	
public:
	Sprite();
	Sprite(Texture* texture, int timeAnimation);
	Sprite(Texture* texture, int timeAnimation, int startIndex, int endIndex);
	void SelectIndex(int);
	//next sprite in list
	void Next();
	void Update(int t);
	//Render current sprite in location(x,y) at the target surface
	void Draw(int x, int y);
	~Sprite();
};
#endif SPRITE_H