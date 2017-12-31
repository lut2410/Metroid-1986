#ifndef RIPPER_H
#define RIPPER_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
enum RipperAction{
	SuftToLeft,
	SuftToRight

};
class Ripper : public GameObject{
	RipperAction _action;
public:
	Ripper();
	Ripper(int x, int y, int type = 1);
	~Ripper();
	void UpdateActionAndVelocity(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void Draw(Camera* camera);
	void handleCollision(map<int, GameObject*> objectList, float dt);
};

#endif