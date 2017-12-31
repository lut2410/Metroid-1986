#ifndef WAVER_H
#define WAVER_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define PI 3.14159265
#define TIME_A_CYCLE 1000//1s
enum WaverAction{
	SuftToLeft_WaverA,
	SuftToRight_WaverA

};
class Waver : public GameObject{
	WaverAction _action;
	int _originposY;		//the origin coordinates (Y)
	DWORD _localTime;
	int AMPLITUDE;
public:
	Waver();
	Waver(int x, int y, int type = 1);
	~Waver();
	void Update(int deltaTime);
	void UpdateAnimationBaseOnStatus();
	void Draw(Camera* camera);
	void handleCollision(map<int, GameObject*> objectList, float dt);

};

#endif