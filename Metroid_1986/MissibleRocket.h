#ifndef MISSIBLEROCKET_H
#define MISSIBLEROCKET_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
class MissibleRocket : public GameObject{

public:
	MissibleRocket();
	MissibleRocket(int x, int y);
	~MissibleRocket();
};

#endif