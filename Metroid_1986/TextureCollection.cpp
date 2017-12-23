#include "TextureCollection.h"
TextureCollection* TextureCollection::textureCollection = NULL;
TextureCollection::TextureCollection(){

	playerTexture2 = new Texture2("Resources/Image/player/image.png", "Resources/Image/player/player.txt");
	bulletTexture2 = new Texture2("Resources/Image/player/image.png", "Resources/Image/player/bullet.txt");
	explodeTexture2 = new Texture2("Resources/Image/player/image.png", "Resources/Image/player/explode.txt");
	hedgehogTexture2 = new Texture2("Resources/Image/Enemy/image.png", "Resources/Image/enemy/hedgehog.txt");
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
	case Hedgehog_ID:
		return hedgehogTexture2;
		break;
	case ExplodeObject_ID:
		return explodeTexture2;
	}
};
