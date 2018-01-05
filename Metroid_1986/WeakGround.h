#ifndef WEAKGROUND_H
#define WEAKGROUND_H
#pragma once
#include "GameObject.h"
class WeakGround :public GameObject{
	//int typeID;
public:
	WeakGround();
	WeakGround(int x, int y, int type = 1);
	void Update(int time);
	void UpdateAnimationBaseOnStatus();
	RECT getCollisionBound();
};
#endif