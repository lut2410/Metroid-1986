#ifndef HPTONIC_H
#define HPTONIC_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define TIMEHPTONIC 2000 //2s
class HPTonic : public GameObject{
	int _remainingTime;		// time survival
public:
	HPTonic();
	HPTonic(int x, int y);
	~HPTonic();
	void Update(int deltaTime);
};

#endif