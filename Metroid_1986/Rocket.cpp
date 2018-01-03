#include "Rocket.h"
Rocket::Rocket()
{}
Rocket::Rocket(int x, int y) :GameObject(Rocket_ID, x, y, 0, 0){
	Texture2* itemTexture = NULL;
	itemTexture = TextureCollection::getInstance()->getTexture2(Rocket_ID);
	_remainingTime = ROCKET_TIME_SURVIVAL;
	//just only have 1 sprite
	_actionAnimation.push_back(new Animation(itemTexture, "Rocket"));

	_currentAnimation = _actionAnimation[0];
}
void Rocket::Update(int deltaTime)
{
	//update remaining-time
	_remainingTime -= deltaTime;
	if (_remainingTime <= 0)
		SetObjectStatus(ObjectStatus::Died_OS);
}