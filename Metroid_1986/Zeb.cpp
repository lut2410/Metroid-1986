#include "Zeb.h"
Zeb::Zeb()
{}
Zeb::Zeb(int x, int y, int type) :GameObject(Zeb_ID, x, y, 0, 0){
	//take texture
	Texture2* zebTexture = NULL;
	zebTexture = TextureCollection::getInstance()->getTexture2(Zeb_ID);

	switch (type)
	{
	case 1:
		_hp = 1;
		_attack = 8;
		OBJECT_VEL = 0.1f;
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(zebTexture, "Type1"));

		break;
	case 2:
		_hp = 2;
		_attack = 10;
		OBJECT_VEL = 0.2f;
		//take animation of its type( type2 in here)
		_actionAnimation.push_back(new Animation(zebTexture, "Type2"));
		break;
	}
	_beWoundingAnimation.push_back(new Animation(zebTexture, "BeWounding"));
	_beFreezingAnimation.push_back(new Animation(zebTexture, "BeFreezing"));

	//set default action and animation
	_action = ZebAction::Up_ZebA;
	_currentAnimation = _actionAnimation[0];	//actually _actionAnimation just have 1 animation 

	//set flying style
	int random = rand() % 2;// random (0->1)
	if (random) //=50%
		_zedFlyingType = ZebFlyingType::Up_Then_Left_ZFT;
	else
		_zedFlyingType = ZebFlyingType::Up_Then_Right_ZFT;

}
void Zeb::UpdateActionAndVelocity(int deltaTime)
{
	//ACTION
	//3% to redirect
	if (_action == ZebAction::Up_ZebA)
	{
		int random = rand() % 100 - 30 * OBJECT_VEL; // random 3%(type 1), 6%(type2)
		if (random < 0) 
			ChangeAction();
	}
	//VEL
	switch (_action)
	{
	case ZebAction::Standstill:
		_velX = 0;
		_velY = 0;
		break;
	case ZebAction::Up_ZebA:
		_velX = 0;
		_velY = OBJECT_VEL;
		break;
	case ZebAction::Left_ZebA:
		_velX = -OBJECT_VEL;
		_velY = 0;
		break;
	case ZebAction::Right_ZebA:
		_velX = OBJECT_VEL;
		_velY = 0;
		break;
	}
}
void Zeb::UpdateAnimationBaseOnStatus()
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
void Zeb::Draw(Camera* camera)
{

	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	switch (_zedFlyingType)
	{
	case ZebFlyingType::Up_Then_Left_ZFT:
		_currentAnimation->Draw(center.x, center.y);
		break;
	case ZebFlyingType::Up_Then_Right_ZFT:
		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	}

}
void Zeb::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	RECT a = getCollisionBound();
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* otherObject = it->second;
		Direction direction;
		//check collision with wall, but don't check with "Pipe produce it"
		if (otherObject->getObjectType() == ObjectType::RelativesWithWall_OT && otherObject->getObjectID() != ObjectID::ZebProductionPipe)
		if (handleObjectCollision(this, otherObject, direction, deltaTime))
		{
			ChangeAction(direction);
		}
	}
}
void Zeb::ChangeAction(Direction collisionDirectionWithWall)
{
	if (_action == ZebAction::Up_ZebA)
	{
		if (_zedFlyingType == ZebFlyingType::Up_Then_Left_ZFT)
			_action = ZebAction::Left_ZebA;
		else
			_action = ZebAction::Right_ZebA;
	}
	else
	{
		//left or right => collide with wall => standstill
		if (collisionDirectionWithWall == Direction::Left_Direction || collisionDirectionWithWall == Direction::Right_Direction) //exception the case collide adjacent top
		_action = ZebAction::Standstill;
	}
		
	
}