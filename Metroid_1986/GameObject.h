#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#pragma once
#include "TextureCollection.h"
#include "Animation.h"
#include "Camera.h"
#include <math.h>
#include <stdlib.h>		//support to random
#define WOUNDED_FRAMES 8
#define FREEZED_FRAMES 30
#define EXPLODE_FRAMES 2
enum ObjectType{
	RelativesWithWall_OT,	//can't move, is in background: ground,wall,gate,door,..
	Player_OT,				//Samus
	Enemy_OT,
	Boss_OT,
	Item_OT
};
enum DirectionOfFace{
	Neutral,
	Left,
	Right
};

enum ObjectStatus{
	Survival_OS,
	BeWounding_OS,
	BeFreezing_OS,
	Exploding_OS,
	Died_OS

};
enum BulletType
{
	IsntBullet,
	BulletFromPlayer_Nomal,
	BulletFromPlayer_Freeze,
	BulletFromPlayer_Wave,
	BulletFromPlayer_Rocket,
	BulletFromSkree,
	BulletFromRidley,
	BulletFromKraid_Boomerang,
	BulletFromKraid_Rocket
};


class GameObject{
protected:
	float OBJECT_VEL;
	ObjectID _objectID;		
	ObjectStatus _objectStatus;
	int _hp;			//HP
	int _attack;		//attack enemy,HP enemy will be subtract = attack index
	int _remainingWoundingTime;		//time to back to normal status
	int _remainingFreezingTime;		//time to back to normal status
	int _remainingExplodeTime;		//time to die status
	bool _activeEnemy;				//some enemy need
	int _remainingTimeToShoot;
	int _remainingTimeToShoot2;
	int _remainingTime;				// time survival

	DirectionOfFace _directionOfFace;	//transform of position X : left or right?
	Animation* _currentAnimation;
	vector<Animation*> _actionAnimation; 
	Animation* explodingAnimation;
	vector<Animation*> _beWoundingAnimation;
	vector<Animation*> _beFreezingAnimation;
	int _currentIndexOfAnimation;				//use when change status to be freezing
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

	virtual D3DXVECTOR2 getPositionOfGun();
	virtual D3DXVECTOR2 getPositionOfGun2();
	virtual RECT getCollisionBound();
	D3DXVECTOR2 getVelocity();
	ObjectID getObjectID();
	ObjectType getObjectType();	//use to check collision
	DirectionOfFace getDirectionOfFace();
	int getAttackDame();
	int getHP();
	bool getActiveEnemy();
	int getRemainingTimeToShoot();
	void SetRemainingTimeToShoot(int time);
	int getRemainingTimeToShoot2();
	void SetRemainingTimeToShoot2(int time);
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
	virtual void BeFreezed(int lossHP = 1);
	void SpecifyStatusWhenHP0();

	//bool enemyCheckExplode(int deltaTime);	//be destroying
};
#endif