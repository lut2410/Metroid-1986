#ifndef ROCKET_H
#define ROCKET_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define ROCKET_TIME_SURVIVAL 2000
class Rocket : public GameObject{

public:
	Rocket();
	Rocket(int x, int y);
	~Rocket();
	void Update(int deltaTime);
};

#endif