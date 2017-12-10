#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#pragma once
#include "TextureCollection.h"
#include "Animation.h"
#include "Camera.h"

enum ObjectStatus{
	Nomal,
	Destroy
};

class GameObject{
protected:
	bool _survive;	//status: survival
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
	virtual void Update(int deltaTime);
	virtual void Draw(Camera* camera);
};
#endif