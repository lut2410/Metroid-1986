#include "Rio.h"
Rio::Rio(){}
Rio::Rio(int x, int y, int type) :GameObject(Rio_ID, x, y, 0, 0){
	//take texture
	Texture2* rioTexture = NULL;
	rioTexture = TextureCollection::getInstance()->getTexture2(Rio_ID);
	_originposY = y;
	_block = Direction::None_Direction;
	switch (type)
	{
	case 1:
		_hp = 3;
		_attack = 8;
		OBJECT_VEL = 0.0625f;
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(rioTexture, "Type1"));
		break;
	case 2:
		_hp = 5;
		_attack = 8;
		OBJECT_VEL = 0.25f;
		_actionAnimation.push_back(new Animation(rioTexture, "Type2"));
		break;
	}
	_beWoundingAnimation.push_back(new Animation(rioTexture, "BeWounding"));
	_beFreezingAnimation.push_back(new Animation(rioTexture, "BeFreezing"));
	//set default action and animation
	_action = RioAction::Nomal_RioA;
	_currentAnimation = _actionAnimation[_action];	//actually _actionAnimation just have 1 animation 
}

void Rio::Update(int deltaTime)
{
	//update status
	if (getObjectType() == ObjectType::Enemy_OT)
		UpdateStatus();

	if (_objectStatus != ObjectStatus::Survival_OS)
		return;
	//except the case waver is freezing => update time=> back to survival => posY is wrong
	//update time
	if (_action == RioAction::Nomal_RioA)
		return;
	_localTime += deltaTime;
	float x = (float)_localTime / TIME_TO_LOWEST;

	//Update velX
	switch (_action)
	{
	case RioAction::Nomal_RioA:
		_velX = 0;
		break;
	case RioAction::AttackToLeft_RioA:
		_velX = -OBJECT_VEL;
		break;
	case RioAction::AttackToRight_RioA:
		_velX = OBJECT_VEL;
		break;

	}
	//Update position
	{
		_posX += _velX * deltaTime;
		_posY = _originposY + AMPLITUDE*(x*x - 2 * x);	//equation about fluctations in veltical
	}

}

void Rio::UpdateAnimationBaseOnStatus()
{
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[0];
		break;
	case ObjectStatus::BeWounding_OS:
		_currentAnimation = _beWoundingAnimation[0];
		_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::BeFreezing_OS:
		_currentAnimation = _beFreezingAnimation[0];
		_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::Exploding_OS:
		_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}

void Rio::handleCollision(int playerX, int playerY, float dt)
{
	//just the case Rio is touch with wall -> check collision base on player
	//else attack to the direction was specified 
	if (_action != RioAction::Nomal_RioA)
		return;
	int distance = abs(this->_posX - playerX);	//X
	AMPLITUDE = abs(this->_posY - playerY);		//
	if (distance <= 75)
	{
		if (_posX > playerX && _block != Direction::Left_Direction)
			_action = RioAction::AttackToLeft_RioA;
			
		if (_posX < playerX && _block != Direction::Right_Direction)
			_action = RioAction::AttackToRight_RioA;
		_originposY = _posY;
		//reset time
		_localTime = 0;
			
	}
}

void Rio::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	RECT a = getCollisionBound();
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* otherObject = it->second;

		if (otherObject->getObjectType() == ObjectType::RelativesWithWall_OT)
		{
			Direction direction;
			if (handleObjectCollision(this, otherObject, direction, deltaTime)) //collision 
			{
				switch (direction)
				{
				case Direction::Top_Direction:
				case Direction::Left_Direction:
				case Direction::Right_Direction:
					_action = RioAction::Nomal_RioA;
					_block = direction;
					break;
				case Direction::Bottom_Direction:
					break;

				}

				break;
			}
		}
	}
}