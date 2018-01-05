#pragma once
#include "Sprite.h"


class SpriteNumber :
	public Sprite
{
	static SpriteNumber* instance;
public:
	static SpriteNumber* getInstance();
	SpriteNumber();
	~SpriteNumber();
	int index;


	void renderNumber(int number, int spriteIndex);
};

