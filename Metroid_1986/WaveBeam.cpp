#include "WaveBeam.h"
WaveBeam::WaveBeam(){}
WaveBeam::WaveBeam(int x, int y) :GameObject(WaveBeam_ID, x, y, 0, 0){
	Texture2* itemTexture = NULL;
	itemTexture = TextureCollection::getInstance()->getTexture2(WaveBeam_ID);

	//just only have 1 sprite
	_actionAnimation.push_back(new Animation(itemTexture, "WaveBeam"));
	_currentAnimation = _actionAnimation[0];
}
