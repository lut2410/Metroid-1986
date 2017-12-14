#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#pragma once
#include "TextureCollection.h"
#include "Animation.h"
#include "Camera.h"
#define WOUNDED_FRAMES 5

enum ObjectStatus{
	Nomal,
	Destroy
};

class GameObject{
protected:
	bool _survive;		//status: survival
	int _beAttacking;	// object is be attacking
	//int _beDestroying;	//object is be destroying
	int _hp;			//HP
	int _attack;		//attack enemy,HP enemy will be subtract = attack index
	ObjectID _objectID;
	Animation* _currentAnimation;
	//Position of Object

	//Velocity of Object
	float _velX;
	float _velY;
	
	//Other Parameters
	void CreateSprite();
public:
	int _posX;
	int _posY;
	GameObject();
	~GameObject();
	GameObject(ObjectID objectID, int posX, int posY, float velX, float velY);
	virtual RECT getCollisionBound();
	D3DXVECTOR2 getVelocity();
	ObjectID getObjectID();
	bool isSurvive();
	//update action and position
	virtual void Update(int deltaTime);			
	//update animation-frame of sprite
	virtual void Update2(int deltaTime);		
	virtual void Draw(Camera* camera);
	virtual void handleCollision(map<int, GameObject*> objectList, float dt);
	virtual void IsWounded(int lossHP=1);		//be wounded 'lossHP' HP
};
#endif