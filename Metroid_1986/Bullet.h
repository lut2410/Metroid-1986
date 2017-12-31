#ifndef BULLET_H
#define BULLET_H

#pragma once
//#include "Player.h"
#include "GameObject.h"
#include "Collision.h"

#define BULLET_VEL 0.3f
enum BulletType
{
	BulletFromPlayer_Nomal,
	BulletFromPlayer_Freeze,
	BulletFromSkree
};

class Bullet: public GameObject{
	int _remainingTime;		// time survival
public:
	Bullet();
	Bullet(BulletType bulletType, int x, int y, Direction directionFly, DWORD survivalTime = 200);
	~Bullet();
	//void BeWounded(int hp);
	void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void handleCollision(map<int, GameObject*> objectList, float dt);
};

#endif