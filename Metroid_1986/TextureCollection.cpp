#include "TextureCollection.h"
TextureCollection* TextureCollection::textureCollection = NULL;
TextureCollection::TextureCollection(){

	playerTexture2 = new Texture2("Resources/Image/player/sprite.png", "Resources/Image/player/sprite.txt");
	bulletTexture2 = new Texture2("Resources/Image/player/sprite.png", "Resources/Image/player/bullet.txt");
};
TextureCollection* TextureCollection::getInstance(){
	if (textureCollection == NULL)
		textureCollection = new TextureCollection();
	return textureCollection;
}

Texture2* TextureCollection::getTexture2(ObjectID id){
	switch (id)
	{
	case Player_ID:
		return playerTexture2;
		break;
	case Bullet_ID:
		return bulletTexture2;
		break;
	}
};
