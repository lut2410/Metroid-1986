#include "Skree.h"
Skree::Skree()
{}
Skree::Skree(int x, int y, int type) :GameObject(Skree_ID, x, y, 0, 0){
	//take texture
	Texture2* skreeTexture = NULL;
	skreeTexture = TextureCollection::getInstance()->getTexture2(Skree_ID);

	switch (type)
	{
	case 1:
		_hp = 3;
		_attack = 8;
		//take animation of its type( type1 in here)
		_actionAnimation.resize(3);
		_actionAnimation[Nomal_SA]			= new Animation(skreeTexture, "Type1:NomalOrDive");
		_actionAnimation[Dive_SA]			= new Animation(skreeTexture, "Type1:NomalOrDive");
		_actionAnimation[BeAttacking_SA]	= new Animation(skreeTexture, "Type1:BeAtacking");
		break;
	case 2:
		_hp = 5;
		_attack = 8;
		_actionAnimation.resize(3);
		_actionAnimation[Nomal_SA]			= new Animation(skreeTexture, "Type2:NomalOrDive");
		_actionAnimation[Dive_SA]			= new Animation(skreeTexture, "Type2:NomalOrDive");
		_actionAnimation[BeAttacking_SA]	= new Animation(skreeTexture, "Type2:BeAtacking");
		break;
	}

	//set default action and animation
	_action = SkreeAction::Nomal_SA;
	_currentAnimation = _actionAnimation[_action];	//actually _actionAnimation just have 1 animation 
}
void Skree::Update(int deltaTime)
{
	
	//specify action
	if (_beAttacking)
	{
		_action = SkreeAction::BeAttacking_SA;
		_beAttacking--;
		if (_beAttacking == 0)
			//back to dive
			_action = SkreeAction::Dive_SA;
	}

	//specify vel
	switch (_action)
	{
	case SkreeAction::Nomal_SA:		//crawl right
		_velX = 0;
		_velY = 0;
		break;
	case SkreeAction::Dive_SA:
		_velX = 0;
		_velY = -SKREE_VEL;
		break;
	case SkreeAction::BeAttacking_SA:
		_velX = 0;
		_velY = 0;
		break;
	}

	//update position
	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;
			
}
void Skree::Update2(int deltaTime)
{
	if (enemyCheckExplode(deltaTime))
		return;

	//update animation
	_currentAnimation = _actionAnimation[_action];
	_currentAnimation->Update(deltaTime);
}
void Skree::handleCollision(int playerX, int playerY, float dt)
{
	if (_action == SkreeAction::BeAttacking_SA)
		//be attacking -> inactive-> must not check collision
		return;
	int distance = abs(this->_posX - playerX);
	if (distance <= 50)
	{
		_action = SkreeAction::Dive_SA;
		//dive
	}
	if (_action == SkreeAction::Dive_SA)
	{
		if (_posX > playerX)
			_posX-=2;
		if (_posX < playerX)
			_posX+=2;
	}
	
}
void Skree::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	if (_action == SkreeAction::BeAttacking_SA)
		// inactive-> must not check collision
		return;
	RECT a=getCollisionBound();
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* otherObject = it->second;
		if (otherObject->getObjectID() != ObjectID::Skree_ID)
		{
			Direction direction;
			if (handleObjectCollision(this, otherObject, direction, deltaTime)) //collision 
			{
				switch (otherObject->getObjectID())
				{
				case ObjectID::Ground_ID:
					if (_action==Dive_SA)			//except the case Skree is hanging backward on wall
						this->BeWounded(this->_hp);	//dam dau vao da =>cho chet luon
					break;
				case ObjectID::Zoomer_ID:
					this->BeWounded(otherObject->getAttackDame());
					otherObject->BeWounded(this->getAttackDame());
					break;
				}
			}
		}
	}
}