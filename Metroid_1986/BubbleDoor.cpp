#include "BubbleDoor.h"
BubbleDoor::BubbleDoor()
{}
BubbleDoor::BubbleDoor(int x, int y) :GameObject(BubbleDoor_ID, x, y, 0, 0){
	_isRelativeWithGround = true;

	Texture2* bubbleDoorTexture = NULL;
	bubbleDoorTexture = TextureCollection::getInstance()->getTexture2(BubbleDoor_ID);
	for (int i = 0; i < 4; i++)
		_actionAnimation.push_back( new Animation(bubbleDoorTexture, bubbleDoorTexture->_animationNames.at(i)));

	_action = BubbleDoorAction::Close;
	_currentAnimation = _actionAnimation[_action];
	_countdownFrames = -1;
}
void BubbleDoor::Update(int deltaTime)
{
	//check this time is in PassTheGate?
	if (Camera::getInstance()->_directionOfTheGate)
	{
		//alway open
		_action = BubbleDoorAction::Open;
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
	case BubbleDoorAction::Close:
		//switch to openning
		Openning();
		break;
	case BubbleDoorAction::Openning:
		Open();
		break;
	case BubbleDoorAction::Open:
		//switch to closing
		Closing();
		break;
	case BubbleDoorAction::Closing:
		Close();
		break;
	}
}
void BubbleDoor::BeWounded(int hp)
{
	if (_action==BubbleDoorAction::Close)
	Openning();
}
void BubbleDoor::Open()
{
	_action = BubbleDoorAction::Open;
	_countdownFrames = 30;
}
void BubbleDoor::Close()
{
	_action = BubbleDoorAction::Close;
	_countdownFrames = -1;
}
void BubbleDoor::Openning()
{
	_action = BubbleDoorAction::Openning;
	_countdownFrames = 3;
}
void BubbleDoor::Closing()
{
	_action = BubbleDoorAction::Closing;
	_countdownFrames = 3;
}
BubbleDoor::~BubbleDoor()
{}