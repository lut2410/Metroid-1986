#include "MaruMari.h"
MaruMari::MaruMari()
{}
MaruMari::MaruMari(int x, int y) :GameObject(MaruMari_ID, x, y, 0, 0){
	Texture2* itemTexture = NULL;
	itemTexture = TextureCollection::getInstance()->getTexture2(MaruMari_ID);

	//just only have 1 sprite
	_actionAnimation.push_back(new Animation(itemTexture, "MaruMari"));
	_currentAnimation = _actionAnimation[0];
}