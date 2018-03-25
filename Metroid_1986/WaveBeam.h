#ifndef WAVEBEAM_H
#define WAVEBEAM_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
class WaveBeam : public GameObject{

public:
	WaveBeam();
	WaveBeam(int x, int y);
	~WaveBeam();
};

#endif