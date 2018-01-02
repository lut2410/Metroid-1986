#ifndef ZEBPRODUCTIONPIPE_H
#define ZEBPRODUCTIONPIPE_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define TIME_TO_PRODUCE_NEW_ZEB 5000 //5s //actually, check Zeb whether is dead or not-> produce
enum ZebProductionPipeAction{
	ReadyProduce_ZebProductionPipeA,
	DontReadyProduce_ZebProductionPipeA,
};
class ZebProductionPipe : public GameObject{
	ZebProductionPipeAction _action;
	int _remainningTime;
public:
	ZebProductionPipe();
	ZebProductionPipe(int x, int y, int type = 1);
	~ZebProductionPipe();
	void Update(int deltaTime);
	void Draw(Camera* camera);
};

#endif