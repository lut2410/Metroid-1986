#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#pragma once
#include "Sprite.h"
#include "TextureCollection.h"

class GameObject{
protected:
	ObjectID _objectID;
	Sprite* _sprite;
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
};
#endif