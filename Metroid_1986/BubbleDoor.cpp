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
}

void BubbleDoor::Update2(int deltaTime)
{
	_currentAnimation = _actionAnimation[_action];
	_currentAnimation->Update(deltaTime);
}
BubbleDoor::~BubbleDoor()
{}