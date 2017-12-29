#ifndef ZOOMER_H
#define ZOOMER_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define ZOOMER_VEL 0.1f
enum ZoomerAction{
	Crawl_Top,
	Crawl_Right,
	Crawl_Bottom,
	Crawl_Left,
	Crawl_Top_BeAttacking,
	Crawl_Right_BeAttacking,
	Crawl_Bottom_BeAttacking,
	Crawl_Left_BeAttacking
	

};
class Zoomer: public GameObject{
	ZoomerAction _action;
public:
	Zoomer();
	Zoomer(int x, int y, int type = 1);
	~Zoomer();
	void Update(int deltaTime);
	void Update2(int deltaTime);
	void handleCollision(map<int, GameObject*> objectList, float dt);
	//int IsCollideVsWall(GameObject* considerObject, GameObject* otherObject, Direction& direction, int dt);
	// foot on the wall => /16 (use to change direction)
	void FixPosition();
};

#endif