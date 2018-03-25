#ifndef RIO_H
#define RIO_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define PI 3.14159265
#define TIME_TO_LOWEST 1000//1s
enum RioAction{
	Nomal_RioA,	//observe
	AttackToLeft_RioA,
	AttackToRight_RioA

};
class Rio : public GameObject{
	RioAction _action;
	int _originposY;		//the origin coordinates (Y)
	DWORD _localTime;
	int AMPLITUDE;			//amplitude : Rio fly to lowest = position of player
	Direction _block;
public:
	Rio();
	Rio(int x, int y, int type = 1);
	~Rio();
	void Update(int deltaTime);
	//void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void handleCollision(int playerX, int playerY, float dt);
	void handleCollision(map<int, GameObject*> objectList, float dt);

};

#endif