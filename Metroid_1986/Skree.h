#ifndef SKREE_H
#define SKREE_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
//#define SKREE_VEL 0.2f
enum SkreeAction{
	Nomal_SkreeA,
	Dive_SkreeA,
	BeAttacking_SkreeA

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

class BulletFromSkree : public GameObject{
	int _remainingTime;		// time survival
public:
	BulletFromSkree();
	BulletFromSkree(int x, int y, Direction directionFly, DWORD survivalTime = 200);
	~BulletFromSkree();
	//void BeWounded(int hp);
	void Update(int deltaTime);
	void Update2(int deltaTime);
	void handleCollision(map<int, GameObject*> objectList, float dt);
};
#endif