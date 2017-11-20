#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once
#include "Sprite.h"
class Animation{
	vector<Sprite>* _spriteList;	//list contain sprites
	int _currentIndex;
	int _timeAnimation;
	int _timeLocal;
public:
	Animation();
	Animation(const Animation&);
	Animation(Texture2*, string);
	~Animation();
	
	void SelectIndex(int);
	int getCurrentIndex();
	void Next();						//next sprite in list
	void Update(int t);					//update to next sprite base on time
	//Render current sprite in location(x,y) at the target surface
	void Draw(int x, int y, int index);						//Draw frame has specified index
	void Draw(int x, int y);
	void DrawFlipHorizontal(int x, int y);
};
#endif