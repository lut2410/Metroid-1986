#ifndef FIRE_H
#define FIRE_H
#pragma once
#include "GameObject.h"
class Fire :public GameObject{
	//int typeID;
public:
	Fire();
	Fire(int x, int y, int type = 1);
	void Update(int time);
	void Update2(int time);
	void Draw(Camera* camera);
	RECT getCollisionBound();
};
#endif