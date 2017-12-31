#ifndef SKREE_H
#define SKREE_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#include "Bullet.h"
//#define SKREE_VEL 0.2f
enum SkreeAction{
	Nomal_SkreeA,
	Dive_SkreeA

};
class Skree : public GameObject{
	SkreeAction _action;
public:
	Skree();
	Skree(int x, int y, int type = 1);
	~Skree();
	void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void handleCollision(int playerX, int playerY, float dt);
	void handleCollision(map<int, GameObject*> objectList, float dt);

};

#endif