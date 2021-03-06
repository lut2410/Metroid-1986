#include "Ripper.h"
Ripper::Ripper()
{}
Ripper::Ripper(int x, int y, int type) :GameObject(Ripper_ID, x, y, 0, 0){
	//take texture
	Texture2* ripperTexture = NULL;
	ripperTexture = TextureCollection::getInstance()->getTexture2(Ripper_ID);
	//ripper is stubborn
	_hp = 100;
	switch (type)
	{
	case 1:
		_attack = 8;
		OBJECT_VEL = 0.0625f;
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(ripperTexture, "Type1"));
		break;
	case 2:
		_attack = 10;
		OBJECT_VEL = 0.0625f;
		//take animation of its type( type2 in here)
		_actionAnimation.push_back(new Animation(ripperTexture, "Type2"));
		break;
	case 3:
		_attack = 12;
		OBJECT_VEL = 0.12f;
		//take animation of its type( type3 in here)
		_actionAnimation.push_back(new Animation(ripperTexture, "Type3"));
		break;
	}
	_beWoundingAnimation.push_back(new Animation(ripperTexture, "BeWounding"));
	_beFreezingAnimation.push_back(new Animation(ripperTexture, "BeFreezing"));
	//set default action and animation
	_action = RipperAction::SuftToLeft_RipperA;
	_currentAnimation = _actionAnimation[_action];	//actually _actionAnimation just have 1 animation 
}
void Ripper::UpdateActionAndVelocity(int deltaTime)
{
	//specify vel
	switch (_action)
	{
	case RipperAction::SuftToLeft_RipperA:
		_velX = -OBJECT_VEL;
		_velY = 0;
		break;
	case RipperAction::SuftToRight_RipperA:
		_velX = OBJECT_VEL;
		_velY = 0;
		break;
	}
}
void Ripper::Update(int deltaTime)
{
	//update status
	UpdateStatus();
	//Update action and velocity
	UpdateActionAndVelocity(deltaTime);
	//update position
	if (_objectStatus == Survival_OS
		|| _objectStatus == BeWounding_OS)
	{
		_posX += _velX * deltaTime;
		_posY += _velY * deltaTime;
	}

}
void Ripper::UpdateAnimationBaseOnStatus()
{
	// virtual void
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
void Ripper::Draw(Camera* camera)
{

	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	switch (_action)
	{
	case RipperAction::SuftToLeft_RipperA:		
		_currentAnimation->Draw(center.x, center.y);
		break;
	case RipperAction::SuftToRight_RipperA:
		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	}
	
}
void Ripper::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	RECT a = getCollisionBound();
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* otherObject = it->second;
		Direction direction;
		if (otherObject->getObjectID() == ObjectID::Ground_ID)
			if (handleObjectCollision(this, otherObject, direction, deltaTime))
			{
				if (_action == RipperAction::SuftToLeft_RipperA)			
					_action = RipperAction::SuftToRight_RipperA;
				else
					_action = RipperAction::SuftToLeft_RipperA;
				break;
			}
		//exit for loop
		//except the case Ripper touch 2 object Ground at the same time 
		//=> SuftToLeft->SuftToRight->SuftToLeft (will be stucked)

	}
}
