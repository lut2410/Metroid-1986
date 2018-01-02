#include "Waver.h"
Waver::Waver()
{}
Waver::Waver(int x, int y, int type) :GameObject(Waver_ID, x, y, 0, 0){
	//take texture
	Texture2* waverTexture = NULL;
	waverTexture = TextureCollection::getInstance()->getTexture2(Waver_ID);
	_originposY = y;
	switch (type)
	{
	case 1:
		_hp = 3;
		_attack = 8;
		OBJECT_VEL = 0.0625f;
		AMPLITUDE = 64;
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(waverTexture, "Type1"));
		break;
	case 2:
		_hp = 5;
		_attack = 8;
		OBJECT_VEL = 0.125f;
		AMPLITUDE = 100;
		_actionAnimation.push_back(new Animation(waverTexture, "Type2"));
		break;
	}
	//_beWoundingAnimation.push_back(new Animation(waverTexture, "BeWounding"));	//normal bullet: isn't wounding
	_beFreezingAnimation.push_back(new Animation(waverTexture, "BeFreezing"));
	//set default action and animation
	_action = WaverAction::WaveToLeft_WaverA;
	_currentAnimation = _actionAnimation[0];	//actually _actionAnimation just have 1 animation 
}
RECT Waver::getCollisionBound()
{
	Box objectBox = { 0, 0, 16, 12 };

	RECT objectBound = { _posX - objectBox.width / 2,		//left
		_posY + objectBox.height / 2,						//top
		_posX + objectBox.width / 2,						//right
		_posY - objectBox.height / 2 };						//bottom
	return objectBound;
}
void Waver::Update(int deltaTime)
{
	

	//update status
	if (getObjectType() == ObjectType::Enemy_OT)
		UpdateStatus();

	if (_objectStatus != ObjectStatus::Survival_OS)
		return;
	//except the case waver is freezing => update time=> back to survival => posY is wrong
	//update time
	_localTime += deltaTime;
	if (_localTime >= TIME_A_CYCLE)
		_localTime -= TIME_A_CYCLE;
	float angle = (float) _localTime / TIME_A_CYCLE * PI;
	//Update velX
	switch (_action)
	{
	case WaverAction::WaveToLeft_WaverA:		
		_velX = -OBJECT_VEL;
		break;
	case WaverAction::WaveToRight_WaverA:
		_velX = OBJECT_VEL;
		break;

	}
	//Update position
	{
		_posX += _velX * deltaTime;
		if (_action == WaverAction::WaveToLeft_WaverA || _action == WaverAction::WaveToRight_WaverA)
			//suft to left/right -> posY = const;
		_posY = _originposY + AMPLITUDE* sin(angle);
	}

}
void Waver::UpdateAnimationBaseOnStatus()
{
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[0];
		break;
	case ObjectStatus::BeWounding_OS:
		//_currentAnimation = _beWoundingAnimation[0];
		break;
	case ObjectStatus::BeFreezing_OS:
		_currentAnimation = _beFreezingAnimation[0];
		_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::Exploding_OS:
		_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		//Create bullets
		break;
	}
}

void Waver::Draw(Camera* camera)
{

	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	switch (_action)
	{
	case WaverAction::WaveToLeft_WaverA:
		_currentAnimation->Draw(center.x, center.y);
		break;
	case WaverAction::WaveToRight_WaverA:
		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	}

}
void Waver::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	RECT a = getCollisionBound();
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* otherObject = it->second;
		Direction direction;
		if (otherObject->getObjectID() == ObjectID::Ground_ID)
		if (handleObjectCollision(this, otherObject, direction, deltaTime))
		{
			switch (direction)
			{
			case Direction::Top_Direction:
			case Direction::Bottom_Direction:
				//if (_action == WaverAction::WaveToRight_WaverA)
				//	_action = WaverAction::SuftToRight_WaverA;
				//	
				//if (_action == WaverAction::WaveToLeft_WaverA)
				//	_action = WaverAction::SuftToLeft_WaverA;
				break;
			case Direction::Left_Direction:
				_action = WaverAction::WaveToRight_WaverA;
				break;
			case Direction::Right_Direction:
				_action = WaverAction::WaveToLeft_WaverA;
				break;

			}
			break;
		}
		//exit for loop


	}
}
