#ifndef ZEB_H
#define ZEB_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define ZEB_VEL 0.1f
enum ZebAction{
	Standstill,
	Up_ZebA,
	Left_ZebA,
	Right_ZebA
};
enum ZebFlyingType
{
	Up_Then_Left_ZFT,
	Up_Then_Right_ZFT
};
class Zeb : public GameObject{
	ZebFlyingType _zedFlyingType;	//random
	ZebAction _action;				//current ation
public:
	Zeb();
	Zeb(int x, int y, int type = 1);
	~Zeb();
	void Update(int deltaTime);
	void Draw(Camera* camera);
	void handleCollision(map<int, GameObject*> objectList, float dt);
	void ChangeAction(Direction collisionDirectionWithWall = Direction::None_Direction);
};

#endif