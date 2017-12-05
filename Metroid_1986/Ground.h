#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include "GameObject.h"
class Ground:public GameObject{
	//int typeID;
public:
	Ground();
	Ground(int x, int y);
	RECT getCollisionBound();
};
#endif