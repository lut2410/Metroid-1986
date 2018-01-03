#ifndef RIDLEY_H
#define RIDLEY_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define RIDLEY_MAX_VEL_JUMP 0.3f
#define RIDLEY_ACCELERATION -0.01f
#define RIDLEY_TIME_TO_JUMP 1000//1s
#define RIDLEY_TIME_TO_SHOOT 500//0.5s
enum RidleyAction{
	Stand_RidleyA,
	Jump_RidleyA

};
class Ridley : public GameObject{
	RidleyAction _action;
	int _remainingTimeToJump;
public:
	Ridley();
	Ridley(int x, int y);
	~Ridley();
	//void Update(int deltaTime);
	RECT getCollisionBound();
	D3DXVECTOR2 getPositionOfGun();			//bullet fly-out from mouth
	void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void handleCollision(int playerX, int playerY, float dt);
	void handleCollision(map<int, GameObject*> objectList, float dt);

};

#endif