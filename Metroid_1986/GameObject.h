#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#pragma once
#include "TextureCollection.h"
#include "Animation.h"
#include "Camera.h"
#include <math.h>
#include <stdlib.h>		//support to random
#define WOUNDED_FRAMES 4
#define EXPLODE_FRAMES 2
enum ObjectType{
	RelativesWithWall_OT,	//can't move, is in background: ground,wall,gate,door,..
	Player_OT,				//Samus
	Enemy_OT,
	Item_OT
};
enum ObjectStatus{
	Survival_OS,
	BeWounding_OS,
	Exploding_OS,
	Died_OS

};
enum BulletType
{
	IsntBullet,
	BulletFromPlayer_Nomal,
	BulletFromPlayer_Freeze,
	BulletFromSkree
};


class GameObject{
protected:
	float OBJECT_VEL;
	ObjectID _objectID;		
	ObjectStatus _objectStatus;
	int _hp;			//HP
	int _attack;		//attack enemy,HP enemy will be subtract = attack index
	int _remainingWoundingTime;		//time to back to normal status
	int _remainingExplodeTime;
	
	Animation* _currentAnimation;
	vector<Animation*> _actionAnimation; 
	Animation* explodingAnimation;
	vector<Animation*> _beWoundingAnimation;
	vector<Animation*> _beFreezingAnimation;
	//Position of Object

	//Velocity of Object
	float _velX;
	float _velY;
	
	//Other Parameters
public:
	int _posX;
	int _posY;
	GameObject();
	~GameObject();
	GameObject(ObjectID objectID, int posX, int posY, float velX, float velY);

	virtual RECT getCollisionBound();
	D3DXVECTOR2 getVelocity();
	ObjectID getObjectID();
	ObjectType getObjectType();	//use to check collision
	int getAttackDame();
	int getHP();
	virtual BulletType getBulletType();
	ObjectStatus getObjectStatus();
	void SetObjectStatus(ObjectStatus);
	//update action and position
	void UpdateStatus();
	virtual void UpdateActionAndVelocity(int deltaTime);
	virtual void UpdateAnimationBaseOnStatus();
	virtual void Update(int deltaTime);			
	//update animation-frame of sprite
	virtual void Update2(int deltaTime);		
	virtual void Draw(Camera* camera);
	virtual void handleCollision(map<int, GameObject*> objectList, float dt);	//motion base on other object
	virtual void handleCollision(int playerX, int playerY, float dt);			//motion base on player
	virtual void BeWounded(int lossHP=1);		//be wounded 'lossHP' HP
	void SpecifyStatusWhenHP0();

	//bool enemyCheckExplode(int deltaTime);	//be destroying
};
#endif