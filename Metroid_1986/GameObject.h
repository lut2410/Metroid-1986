#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#pragma once
#include "TextureCollection.h"
#include "Animation.h"
#include "Camera.h"
#include <math.h>
#include <stdlib.h>		//support to random
#define WOUNDED_FRAMES 5
enum ObjectType{
	RelativesWithWall_OT,	//can't move, is in background: ground,wall,gate,door,..
	Player_OT,				//Samus
	Enemy_OT,
	Item_OT
};
enum ObjectStatus{
	Survival_OS,
	BeWounding_OS,
	Destroying_OS,
	Died_OS

};

class GameObject{
protected:
	//ObjectType _objectType;
	ObjectID _objectID;		
	ObjectStatus _objectOS;
	//bool _survive;		//status: survival
	int _hp;			//HP
	int _attack;		//attack enemy,HP enemy will be subtract = attack index
	int _beAttacking;	// object is be attacking
	
	
	Animation* _currentAnimation;
	vector<Animation*> _actionAnimation; 
	Animation* expoldeAnimation;
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
	ObjectStatus getObjectStatus();
	void SetObjectStatus(ObjectStatus);
	//update action and position
	virtual void Update(int deltaTime);			
	//update animation-frame of sprite
	virtual void Update2(int deltaTime);		
	virtual void Draw(Camera* camera);
	virtual void handleCollision(map<int, GameObject*> objectList, float dt);	//motion base on other object
	virtual void handleCollision(int playerX, int playerY, float dt);			//motion base on player
	virtual void BeWounded(int lossHP=1);		//be wounded 'lossHP' HP
	bool enemyCheckExplode(int deltaTime);	//be destroying
};
#endif