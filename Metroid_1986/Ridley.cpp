#include "Ridley.h"
Ridley::Ridley(){}
Ridley::Ridley(int x, int y) :GameObject(Ridley_ID, x, y, 0, 0){
	//take texture
	Texture2* ridleyTexture = NULL;
	ridleyTexture = TextureCollection::getInstance()->getTexture2(Ridley_ID);

	_hp = 100;
	_attack = 16;
	OBJECT_VEL = 0.0625f;
	//take animation of its type( type1 in here)
	_actionAnimation.push_back(new Animation(ridleyTexture, "Stand"));
	_actionAnimation.push_back(new Animation(ridleyTexture, "Jump"));

	//_beWoundingAnimation.push_back(new Animation(ridleyTexture, "BeWounding"));
	//_beFreezingAnimation.push_back(new Animation(ridleyTexture, "BeFreezing"));
	
	//set default action and animation
	_action = RidleyAction::Stand_RidleyA;
	_currentAnimation = _actionAnimation[_action];	//actually _actionAnimation just have 1 animation 
}
//void Ridley::Update(int deltaTime)
//{
//	//update status
//	UpdateStatus();
//	//Update action and velocity
//	UpdateActionAndVelocity(deltaTime);
//	//update position
//	if (_objectStatus == Survival_OS)	
//	{
//		_posX += _velX * deltaTime;
//		_posY += _velY * deltaTime;
//	}
//}
RECT Ridley::getCollisionBound(){
	D3DXVECTOR2 center = D3DXVECTOR2{ (float)_posX, (float)_posY }; 
	//specify center correctly
	switch (_action)
	{
	case RidleyAction::Stand_RidleyA:
		break;
	case RidleyAction::Jump_RidleyA:
		center.y += 3;
		break;
	}
	Box playerBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite

	RECT playerBound = { center.x - playerBox.width / 2,		//left
		center.y + playerBox.height / 2,						//top
		center.x + playerBox.width / 2,						//right
		center.y - playerBox.height / 2 };						//bottom
	return playerBound;
}
D3DXVECTOR2 Ridley::getPositionOfGun()
{
	Box playerBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite
	RECT playerBound = { _posX - playerBox.width / 2,		//left
		_posY + playerBox.height / 2,						//top
		_posX + playerBox.width / 2,						//right
		_posY - playerBox.height / 2 };						//bottom

	return D3DXVECTOR2{ (float) playerBound.right, (float) playerBound.top - 14 };
}
void Ridley::UpdateActionAndVelocity(int deltaTime)
{
	if (_remainingTimeToShoot > 0)
		_remainingTimeToShoot -= deltaTime;

	//VEL
	switch (_action)
	{
	case RidleyAction::Stand_RidleyA:
		_velX = 0;
		_velY = 0;
		break;
	case RidleyAction::Jump_RidleyA:
		_velX = 0;
		_velY += RIDLEY_ACCELERATION;
	}
}

void Ridley::UpdateAnimationBaseOnStatus()
{
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[_action];
		break;
	case ObjectStatus::BeWounding_OS:
		//_currentAnimation = _beWoundingAnimation[0];
		//_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::BeFreezing_OS:
		//_currentAnimation = _beFreezingAnimation[_action];
		//_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::Exploding_OS:
		_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}

void Ridley::handleCollision(int playerX, int playerY, float dt)
{
	//active when player come close

	int distance = abs(this->_posX - playerX);	//X
	//int distanceY = abs(this->_posY - playerY);	//Y
	if (distance <= 150)
		_activeEnemy = true;
	else
		_activeEnemy = false;
}

void Ridley::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	if (_activeEnemy == false)
		return;
	RECT a = getCollisionBound();
	Direction direction;
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* otherObject = it->second;

		if (otherObject->getObjectType() == ObjectType::RelativesWithWall_OT)
		{
			if (handleObjectCollision(this, otherObject, direction, deltaTime)) //collision 
			{
				switch (direction)
				{
				case Direction::Top_Direction:
				case Direction::Left_Direction:
				case Direction::Right_Direction:
				/*	break;*/
				case Direction::Bottom_Direction:
					switch (_action)
					{
					case RidleyAction::Stand_RidleyA:
						if (_remainingTimeToJump <= 0)
							//switch to Jump
						{
							_action = RidleyAction::Jump_RidleyA;
							_velY = RIDLEY_MAX_VEL_JUMP;
						
						}
						else
							//continue to standing
						{
							_remainingTimeToJump -= deltaTime;
						}
						break;
					case RidleyAction::Jump_RidleyA:
						_action = RidleyAction::Stand_RidleyA;
						_remainingTimeToJump = RIDLEY_TIME_TO_JUMP;
						break;
						
					}
					break;

				}

				break;
			}
		}
	}
	if(direction != Direction::Bottom_Direction)
		_action = RidleyAction::Jump_RidleyA;
}