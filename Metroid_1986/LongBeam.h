#ifndef LONGBEAM_H
#define LONGBEAM_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
class LongBeam : public GameObject{

public:
	LongBeam();
	LongBeam(int x, int y);
	~LongBeam();
};

#endif