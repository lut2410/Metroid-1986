#include "HPTonic.h"
HPTonic::HPTonic()
{}
HPTonic::HPTonic(int x, int y) :GameObject(HPTonic_ID, x, y, 0, 0){
	Texture2* itemTexture = NULL;
	itemTexture = TextureCollection::getInstance()->getTexture2(HPTonic_ID);

	//just only have 1 sprite
	_actionAnimation.push_back(new Animation(itemTexture, "HPTonic"));
	_currentAnimation = _actionAnimation[0];

	_remainingTime = TIMEHPTONIC;
}
void HPTonic::Update(int deltaTime)
{
	//update remaining-time
	_remainingTime -= deltaTime;
	if (_remainingTime <= 0)
		SetObjectStatus(ObjectStatus::Died_OS);
}