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
		OBJECT_VEL = 0.15;
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(skreeTexture, "Type1"));
		break;
	case 2:
		_hp = 5;
		_attack = 8;
		OBJECT_VEL = 0.25f;
		_actionAnimation.push_back(new Animation(skreeTexture, "Type2"));
		break;
	}

	//set default action and animation
	_action = SkreeAction::Nomal_SkreeA;
	_currentAnimation = _actionAnimation[_action];	//actually _actionAnimation just have 1 animation 
}
void Skree::UpdateActionAndVelocity(int deltaTime)
{
	//VEL
	switch (_action)
	{
	case SkreeAction::Nomal_SkreeA:		//crawl right
		_velX = 0;
		_velY = 0;
		break;
	case SkreeAction::Dive_SkreeA:
		_velX = 0;
		_velY = -OBJECT_VEL;
		break;
	case SkreeAction::BeAttacking_SkreeA:
		_velX = 0;
		_velY = 0;
		break;
	}

}
void Skree::UpdateAnimationBaseOnStatus()
{
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[0];
		break;
	case ObjectStatus::BeWounding_OS:
		_currentAnimation = _beWoundingAnimation[0];
		break;
	case ObjectStatus::Exploding_OS:
		_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		//create bullet
		break;
	}
}

void Skree::handleCollision(int playerX, int playerY, float dt)
{
	if (_action == SkreeAction::BeAttacking_SkreeA)
		//be attacking -> inactive-> must not check collision
		return;
	int distance = abs(this->_posX - playerX);
	if (distance <= 50)
	{
		_action = SkreeAction::Dive_SkreeA;
		//dive
	}
	if (_action == SkreeAction::Dive_SkreeA)
	{
		if (_posX > playerX)
			_posX-=2;
		if (_posX < playerX)
			_posX+=2;
	}
	
}
void Skree::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	if (_action == SkreeAction::BeAttacking_SkreeA)
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
					if (_action==Dive_SkreeA)			//except the case Skree is hanging backward on wall
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