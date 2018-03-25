#ifndef INFOR_H
#define INFOR_H
#pragma once
#include "Font.h"
#include <d3dx9.h>
#include "GameObject.h"
class Infor{
	static Animation* _currentArmedAnimation;
	static Animation* _rocketAnimation;
public:
	Infor();
	static void switchToOtherBulletType(BulletType bulletType);
	static void draw(int hp, int rocketnumber);
};
#endif