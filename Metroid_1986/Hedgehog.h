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
	Crawl_Left
};
class Hedgehog: public GameObject{
	HedgehogAction _action;
	vector<Animation*> _actionAnimation;
public:
	Hedgehog();
	Hedgehog(int x, int y);
	~Hedgehog();
	void Update(int deltaTime);
	void Update2(int deltaTime);
	void handleCollision(map<int, GameObject*> objectList, float dt);
	void FixPosition();
	int IsCollideVsWall(GameObject* considerObject, GameObject* otherObject, Direction& direction, int dt);
};

#endif