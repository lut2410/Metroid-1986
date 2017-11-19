#ifndef SPRITE_H
#define SPRITE_H

#pragma once
#include "Texture2.h"
class Sprite {

protected:
	//Texture* _texture;
	Texture2* _texture2;
	int _startIndex;		
	int _endIndex;		
	int _currentIndex;		
	int _timeAnimation;	
	int _timeLocal;	
	
public:
	Sprite();
	Sprite(Texture2* texture, int timeAnimation);
	Sprite(Texture2* texture, int timeAnimation, int startIndex, int endIndex);
	void SelectIndex(int);
	int getCurrentIndex();
	//next sprite in list
	void Next();
	void Update(int t);
	//Render current sprite in location(x,y) at the target surface
	void Draw(int x, int y, int index);						//Draw frame has specified index
	void Draw(int x, int y);
	void DrawFlipHorizontal(int x, int y);
	~Sprite();
};
#endif SPRITE_H