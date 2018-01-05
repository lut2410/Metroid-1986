#include "Kraid.h"
Kraid::Kraid(){}
Kraid::Kraid(int x, int y,int type) :GameObject(Kraid_ID, x, y, 0, -0.001f){
	//take texture
	_remainingTimeToShoot = 3*KRAID_TIME_TO_SHOOT;
	Texture2* kraidTexture = NULL;
	kraidTexture = TextureCollection::getInstance()->getTexture2(Kraid_ID);

	switch (type)
	{
	case 1:
		_hp = 100;
		_attack = 8;
		OBJECT_VEL = 0.0625f;
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(kraidTexture, "Type1"));
		break;
	case 2:
		_hp = 100;
		_attack = 10;
		OBJECT_VEL = 0.1f;
		//take animation of its type( type2 in here)
		_actionAnimation.push_back(new Animation(kraidTexture, "Type2"));
		break;
	}
	_beWoundingAnimation.push_back(new Animation(kraidTexture, "BeFreezing"));	//don't found yet
	_beFreezingAnimation.push_back(new Animation(kraidTexture, "BeFreezing"));
	//set default action and animation
	_directionOfFace = DirectionOfFace::Neutral;
	_action = KraidAction::RunToRight_KraidA;
	_currentAnimation = _actionAnimation[0];	//actually _actionAnimation just have 1 animation 
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

//RECT Kraid::getCollisionBound(){
//	D3DXVECTOR2 center = D3DXVECTOR2{ (float)_posX, (float)_posY };
//	//specify center correctly
//	switch (_action)
//	{
//	case RidleyAction::Stand_RidleyA:
//		break;
//	case RidleyAction::Jump_RidleyA:
//		center.y += 3;
//		break;
//	}
//	Box playerBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite
//
//	RECT playerBound = { center.x - playerBox.width / 2,		//left
//		center.y + playerBox.height / 2,						//top
//		center.x + playerBox.width / 2,						//right
//		center.y - playerBox.height / 2 };						//bottom
//	return playerBound;
//}
D3DXVECTOR2 Kraid::getPositionOfGun()
{
	Box kraidBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite
	RECT playerBound = { _posX - kraidBox.width / 2,		//left
		_posY + kraidBox.height / 2,						//top
		_posX + kraidBox.width / 2,							//right
		_posY - kraidBox.height / 2 };						//bottom
	if (_directionOfFace == DirectionOfFace::Right)
		return D3DXVECTOR2{ (float)playerBound.right, (float)playerBound.top - 14 };
	else
		return D3DXVECTOR2{ (float)playerBound.left, (float)playerBound.top - 14 };
}
D3DXVECTOR2 Kraid::getPositionOfGun2()
{
	Box kraidBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite
	RECT playerBound = { _posX - kraidBox.width / 2,		//left
		_posY + kraidBox.height / 2,						//top
		_posX + kraidBox.width / 2,							//right
		_posY - kraidBox.height / 2 };						//bottom
	if (_directionOfFace == DirectionOfFace::Right)
		return D3DXVECTOR2{ (float)playerBound.left, (float)playerBound.top - 14 };
	else
		return D3DXVECTOR2{ (float)playerBound.right, (float)playerBound.top - 14 };

}
void Kraid::UpdateActionAndVelocity(int deltaTime)
{
	if (_remainingTimeToShoot > 0)
		_remainingTimeToShoot -= deltaTime;
	if (_remainingTimeToShoot2 >= 0)
		_remainingTimeToShoot2 -= deltaTime;

	//VEL
	switch (_action)
	{
	case KraidAction::RunToLeft_KraidA:
		_velX = -OBJECT_VEL;
		break;
	case KraidAction::RunToRight_KraidA:
		_velX = OBJECT_VEL;
	}
}

void Kraid::UpdateAnimationBaseOnStatus()
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

void Kraid::handleCollision(int playerX, int playerY, float dt)
{
	//active when player come close

	int distanceX = abs(this->_posX - playerX);	//X
	int distanceY = abs(this->_posY - playerY);	//Y
	if (distanceX <= 150 && distanceY <= 100)
	{
		_activeEnemy = true;
		//_remainingTimeToRedirect = 100;
	}
		
	else
		_activeEnemy = false;
	
	//get away when Kraid is near player
	if (_posX < playerX)
	{
		
		if (_posX + 40 >= playerX)
			_action = KraidAction::RunToLeft_KraidA;
	}
	else //if (_posX > playerX)
	{
		//get away when Kraid is near player
		if (_posX - 40 <= playerX)
			_action = KraidAction::RunToRight_KraidA;
	}

	if (_remainingTimeToRedirect > 0)
	{
		_remainingTimeToRedirect -= dt;
		return;
	}
	//else=>check position with player

	//specify kraid direction
	if (_directionOfFace != DirectionOfFace::Neutral)
		//if neutral => don't redirect
		if (_posX > playerX)
			_directionOfFace = DirectionOfFace::Left;
		else
			_directionOfFace = DirectionOfFace::Right;


	if (_posX < playerX)
	{
		_action = KraidAction::RunToRight_KraidA;
		////get away when Kraid is near player
		//if (_posX + 20 >= playerX)
		//	_action = KraidAction::RunToLeft_KraidA;
	}
	if (_posX > playerX)
	{
		_action = KraidAction::RunToLeft_KraidA;
		////get away when Kraid is near player
		//if (_posX - 20 <= playerX)
		//	_action = KraidAction::RunToRight_KraidA;
	}

	_remainingTimeToRedirect = KRAID_TIME_TO_REDIRECT;
}
void Kraid::Draw(Camera* camera)
{
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);

	switch (_directionOfFace)
	{
	case DirectionOfFace::Right:
		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	case DirectionOfFace::Neutral:
	case DirectionOfFace::Left:
		_currentAnimation->Draw(center.x, center.y);
		break;
	}

}

void Kraid::handleCollision(map<int, GameObject*> objectList, float deltaTime)
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
				//case Direction::Top_Direction:	//don't occur
				case Direction::Left_Direction:
					_action = KraidAction::RunToRight_KraidA;
					break;
				case Direction::Right_Direction:
					_action = KraidAction::RunToLeft_KraidA;
					break;
				case Direction::Bottom_Direction:
					_directionOfFace = DirectionOfFace::Right;
					_velY = 0;
					_posY++;
					break;

				}

				break;
			}
		}
	}
	if (direction == Direction::None_Direction&&_directionOfFace==DirectionOfFace::Neutral)	//fall down
		_velY += KRAID_ACCELERATION;
}