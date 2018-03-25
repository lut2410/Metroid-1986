#ifndef ICEBEAM_H
#define ICEBEAM_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
class IceBeam : public GameObject{

public:
	IceBeam();
	IceBeam(int x, int y);
	~IceBeam();
};

#endif