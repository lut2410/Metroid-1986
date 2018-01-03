#include "IceBeam.h"
IceBeam::IceBeam()
{}
IceBeam::IceBeam(int x, int y) :GameObject(IceBeam_ID, x, y, 0, 0){
	Texture2* itemTexture = NULL;
	itemTexture = TextureCollection::getInstance()->getTexture2(IceBeam_ID);

	//just only have 1 sprite
	_actionAnimation.push_back(new Animation(itemTexture, "IceBeam"));
	_currentAnimation = _actionAnimation[0];

}
