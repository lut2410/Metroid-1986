#ifndef MARUMARI_H
#define MARUMARI_H

#pragma once
#include "GameObject.h"
#include "Collision.h"

class MaruMari : public GameObject{
	//bool _beingDestroyed;
public:
	MaruMari();
	MaruMari(int x, int y);
	~MaruMari();
	//void Draw(Camera* camera);
};

#endif