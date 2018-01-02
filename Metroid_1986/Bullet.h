#ifndef BULLET_H
#define BULLET_H

#pragma once
//#include "Player.h"
#include "GameObject.h"
#include "Collision.h"

#define BULLET_VEL 0.2f
#define BULLET_ACCELERATION -0.01f

class Bullet: public GameObject{
	BulletType _bulletType;
	//int _remainingTime;		// time survival

public:
	Bullet();
	Bullet(BulletType bulletType, int x, int y, Direction directionFly, DWORD survivalTime = 300);
	~Bullet();
	//void BeWounded(int hp);
	BulletType getBulletType();
	void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void handleCollision(map<int, GameObject*> objectList, float dt);
};

#endif