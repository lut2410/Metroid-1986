#ifndef HEDGEHOG_H
#define HEDGEHOG_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#include <math.h>
#define HEDGEHOG_VEL 0.1f
enum HedgehogAction{
	Crawl_Top,
	Crawl_Right,
	Crawl_Bottom,
	Crawl_Left,
	Crawl_Top_BeAttacking,
	Crawl_Right_BeAttacking,
	Crawl_Bottom_BeAttacking,
	Crawl_Left_BeAttacking
	

};
class Hedgehog: public GameObject{
	HedgehogAction _action;
public:
	Hedgehog();
	Hedgehog(int x, int y, int type = 1);
	~Hedgehog();
	void Update(int deltaTime);
	void Update2(int deltaTime);
	void handleCollision(map<int, GameObject*> objectList, float dt);
	//int IsCollideVsWall(GameObject* considerObject, GameObject* otherObject, Direction& direction, int dt);
	// foot on the wall => /16 (use to change direction)
	void FixPosition();
};

#endif