#ifndef BULLET_H
#define BULLET_H

#pragma once
#include "GameObject.h"
#include "Collision.h"

#define BULLET_ACCELERATION -0.01f

#define PI 3.14159265
#define WAVEBULLET_TIME_A_CYCLE 100//0.1
class Bullet: public GameObject{
	BulletType _bulletType;
	float BULLET_VEL;

	//use for wavebullet
	int _originpos;		//the origin coordinates
	DWORD _localTime;
	//int AMPLITUDE;	32
public:
	Bullet();
	Bullet(BulletType bulletType, int x, int y, Direction directionFly = Direction::None_Direction, DWORD survivalTime = 300);
	~Bullet();
	//void BeWounded(int hp);
	BulletType getBulletType();
	void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	//void Draw(Camera* camera);
	void handleCollision(map<int, GameObject*> objectList, float dt);
};

#endif