#include "BubbleDoor.h"
BubbleDoor::BubbleDoor()
{}
BubbleDoor::BubbleDoor(int x, int y, int type) :GameObject(BubbleDoor_ID, x, y, 0, 0){
	_type = type;
	Texture2* bubbleDoorTexture = NULL;
	bubbleDoorTexture = TextureCollection::getInstance()->getTexture2(BubbleDoor_ID);
	switch (type)
	{
	case 1:
		_hp = 1;
		_attack = 8;
		OBJECT_VEL = 0.1f;
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Blue:Close"));
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Blue:Open"));
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Blue:Openning"));
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Blue:Closing"));
		break;
	case 2:
		_hp = 5;
		_attack = 10;
		OBJECT_VEL = 0.2f;
		//take animation of its type( type2 in here)
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Red:Close"));
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Red:Open"));
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Red:Openning"));
		_actionAnimation.push_back(new Animation(bubbleDoorTexture, "Red:Closing"));
		break;
	}

	_action = BubbleDoorAction::Close_BDA;
	_currentAnimation = _actionAnimation[_action];
	_countdownFrames = -1;
}
void BubbleDoor::Update(int deltaTime)
{
	//SET BOUND MAP
	//just check with camera
	
	RECT cameraRECT = Camera::getInstance()->getRECT();
	RECT gateRECT = getCollisionBound();
	if (isColliding(cameraRECT, gateRECT))
	{
		D3DXVECTOR2 cameraCenter = { (float)(cameraRECT.left + cameraRECT.right) / 2, (float) (cameraRECT.top + cameraRECT.bottom) / 2 };
		D3DXVECTOR2 gateCenter = { (float)(gateRECT.left + gateRECT.right) / 2, (float)(gateRECT.top + gateRECT.bottom) / 2 };
	
		if (gateCenter.x > cameraCenter.x)//gate is on the right of the camera
			//set rightbound of camera = rightbound of the gate
			Camera::getInstance()->_bound.right = gateCenter.x;
		else //if (gateCenter.x < cameraCenter.x)//gate is on the right of the camera
			Camera::getInstance()->_bound.left = gateCenter.x;
	}
		//this time, the camera is limited by the gate


	//check this time is in PassTheGate?
	if (Camera::getInstance()->_directionOfTheGate)
	{
		//alway open
		_action = BubbleDoorAction::Open_BDA;
		_countdownFrames = 3;
		return;
	}
	//the current action is time up then change to next action
	if (_countdownFrames)
		_countdownFrames--;
	else //the action is time up 
		ChangeAction();
}
void BubbleDoor::Update2(int deltaTime)
{
	_currentAnimation = _actionAnimation[_action];
	_currentAnimation->Update(deltaTime);
}
void BubbleDoor::Draw(Camera* camera)
{
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	_currentAnimation->Draw(center.x, center.y);
}
void BubbleDoor::ChangeAction()
{
	switch (_action){
	case BubbleDoorAction::Close_BDA:
		//switch to openning
		Openning();
		break;
	case BubbleDoorAction::Openning_BDA:
		Open();
		break;
	case BubbleDoorAction::Open_BDA:
		//switch to closing
		Closing();
		break;
	case BubbleDoorAction::Closing_BDA:
		Close();
		break;
	}
}
void BubbleDoor::BeWounded(int hp)
{
	if (_action == BubbleDoorAction::Close_BDA)
	{
		_hp -= hp;
	}
	if(_hp<=0)
		Openning();
}
void BubbleDoor::Open()
{
	_action = BubbleDoorAction::Open_BDA;
	_countdownFrames = 30;
}
void BubbleDoor::Close()
{
	_action = BubbleDoorAction::Close_BDA;
	_countdownFrames = -1;

	//reset HP
	if (_type == 1)
		_hp = 1;
	else
		_hp = 5;
}
void BubbleDoor::Openning()
{
	_action = BubbleDoorAction::Openning_BDA;
	_countdownFrames = 3;
}
void BubbleDoor::Closing()
{
	_action = BubbleDoorAction::Closing_BDA;
	_countdownFrames = 3;
}
BubbleDoor::~BubbleDoor()
{}