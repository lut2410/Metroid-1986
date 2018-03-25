#include "LongBeam.h"
LongBeam::LongBeam()
{}
LongBeam::LongBeam(int x, int y) :GameObject(LongBeam_ID, x, y, 0, 0){
	Texture2* itemTexture = NULL;
	itemTexture = TextureCollection::getInstance()->getTexture2(LongBeam_ID);

	//just only have 1 sprite
	_actionAnimation.push_back(new Animation(itemTexture, "LongBeam"));
	_currentAnimation = _actionAnimation[0];

}
