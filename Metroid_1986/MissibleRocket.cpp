#include "MissibleRocket.h"
MissibleRocket::MissibleRocket()
{}
MissibleRocket::MissibleRocket(int x, int y) :GameObject(MissibleRocket_ID, x, y, 0, 0){
	Texture2* itemTexture = NULL;
	itemTexture = TextureCollection::getInstance()->getTexture2(MissibleRocket_ID);

	//just only have 1 sprite
	_actionAnimation.push_back(new Animation(itemTexture, "MissibleRocket"));
	_currentAnimation = _actionAnimation[0];
}
