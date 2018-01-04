#ifndef GROUND_H
#define GROUND_H
#pragma once
#include "GameObject.h"
class Ground:public GameObject{
	//int typeID;
public:
	Ground();
	Ground(int x, int y, int type = 0);//type:0: normal/type-1: blockY/type-2: blockX
	void Update2(int);
	void Draw(Camera* camera);
	RECT getCollisionBound();
};
#endif