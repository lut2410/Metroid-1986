#ifndef KRAID_H
#define KRAID_H

#pragma once
#include "GameObject.h"
#include "Collision.h"

#define KRAID_ACCELERATION -0.01f
#define KRAID_TIME_TO_REDIRECT 2000	//1s
#define KRAID_TIME_TO_THROW_BOOMERANG 500//0.5s
#define KRAID_TIME_TO_SHOOT 500//0.5s

enum KraidAction{
	RunToLeft_KraidA,
	RunToRight_KraidA
};
class Kraid : public GameObject{
	KraidAction _action;
	int _remainingTimeToRedirect;
public:
	Kraid();
	Kraid(int x, int y, int type = 1);
	~Kraid();
	//void Update(int deltaTime);
	D3DXVECTOR2 getPositionOfGun();			//bullet fly-out from mouth
	D3DXVECTOR2 getPositionOfGun2();		//boomerang fly-out from shoulder
	void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void Draw(Camera* camera);
	void handleCollision(int playerX, int playerY, float dt);
	void handleCollision(map<int, GameObject*> objectList, float dt);

};

#endif