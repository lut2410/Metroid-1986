#ifndef BULLET_H
#define BULLET_H

#pragma once
#include "Player.h"

#define BULLET_VEL 0.3f



class Bullet: public GameObject{
	int _remainingTime;		// time survival
	vector<Animation*> _allAnimation;
public:
	Bullet();
	Bullet(int x, int y, Direction directionFly, DWORD survivalTime = 200);
	~Bullet();
	//void IsWounded(int hp);
	void Update(int deltaTime);
	void Update2(int deltaTime);
};

#endif