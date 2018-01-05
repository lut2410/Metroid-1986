#include "WeakGround.h"

WeakGround::WeakGround(){

}
WeakGround::WeakGround(int x, int y, int type) :GameObject(WeakGround_ID, x, y, 0, 0){
	_hp = type;	
	Texture2* weakGroundTexture = NULL;
	weakGroundTexture = TextureCollection::getInstance()->getTexture2(WeakGround_ID);
	switch (type)
	{
	case 1:
		_actionAnimation.push_back(new Animation(weakGroundTexture, "Orange"));
		break;
	case 2:
		_actionAnimation.push_back(new Animation(weakGroundTexture, "Blue"));

		break;
	}
	_currentAnimation = _actionAnimation[0];	//actually _actionAnimation just have 1 animation 
}
void WeakGround::Update(int deltaTime)
{
	
	//update status
	if (_hp <= 0)
		_objectStatus = ObjectStatus::Died_OS;

}
void WeakGround::UpdateAnimationBaseOnStatus()
{
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[0];
		break;
	case ObjectStatus::BeWounding_OS:
		//_currentAnimation = _actionAnimation[0];
		//_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::BeFreezing_OS:
		//_currentAnimation = _actionAnimation[0];
		//_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::Exploding_OS:
		//_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}
RECT WeakGround::getCollisionBound(){
	//size: 16x16 
	RECT groundBound = { _posX - 8,		//left
		_posY + 8,						//top
		_posX + 8,						//right
		_posY - 8 };					//bottom
	return groundBound;
};