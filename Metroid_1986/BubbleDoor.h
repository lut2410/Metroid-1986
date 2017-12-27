#ifndef BUBBLEDOOR_H
#define BUBBLEDOOR_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
enum BubbleDoorAction{
	Close,
	Open,
	Openning,
	Closing
};
class BubbleDoor : public GameObject{
	BubbleDoorAction _action;
public:
	BubbleDoor();
	BubbleDoor(int x, int y);
	void Update2(int deltaTime);
	~BubbleDoor();
};
#endif