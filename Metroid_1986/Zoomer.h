#ifndef ZOOMER_H
#define ZOOMER_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
enum ZoomerAction{
	Crawl_Top,
	Crawl_Right,
	Crawl_Bottom,
	Crawl_Left

};
class Zoomer: public GameObject{
	ZoomerAction _action;
public:
	Zoomer();
	Zoomer(int x, int y, int type = 1);
	~Zoomer();
	void UpdateActionAndVelocity(int deltaTime);			//use for update()
	void UpdateAnimationBaseOnStatus();		//user for update2()
	void handleCollision(map<int, GameObject*> objectList, float dt);
	//int IsCollideVsWall(GameObject* considerObject, GameObject* otherObject, Direction& direction, int dt);
	// foot on the wall => /16 (use to change direction)
	void FixPosition();
};

#endif