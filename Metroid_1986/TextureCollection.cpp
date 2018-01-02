#include "TextureCollection.h"
TextureCollection* TextureCollection::textureCollection = NULL;
TextureCollection::TextureCollection(){
	doorTexture2		= new Texture2("Resources/Image/Other Object/image.png", "Resources/Image/Other Object/door.txt");
	zebpipeTexture2		= new Texture2("Resources/Image/Other Object/image.png", "Resources/Image/Other Object/Zeb Production Pipe.txt");
	playerTexture2		= new Texture2("Resources/Image/player/image.png", "Resources/Image/player/player.txt");
	bulletTexture2		= new Texture2("Resources/Image/player/image.png", "Resources/Image/player/bullet.txt");
	explodeTexture2		= new Texture2("Resources/Image/player/image.png", "Resources/Image/player/explode.txt");
	zoomerTexture2		= new Texture2("Resources/Image/Enemy/image.png", "Resources/Image/enemy/Zoomer.txt");
	skreeTexture2		= new Texture2("Resources/Image/Enemy/image.png", "Resources/Image/enemy/skree.txt");
	ripperTexture2		= new Texture2("Resources/Image/Enemy/image.png", "Resources/Image/enemy/ripper.txt");
	zebTexture2			= new Texture2("Resources/Image/Enemy/image.png", "Resources/Image/enemy/zeb.txt");
	waverTexture2		= new Texture2("Resources/Image/Enemy/image.png", "Resources/Image/enemy/waver.txt");
	rioTexture2			= new Texture2("Resources/Image/Enemy/image.png", "Resources/Image/enemy/rio.txt");
	itemTexture2		= new Texture2("Resources/Image/item/image.png", "Resources/Image/item/item.txt");


};
TextureCollection* TextureCollection::getInstance(){
	if (textureCollection == NULL)
		textureCollection = new TextureCollection();
	return textureCollection;
}

Texture2* TextureCollection::getTexture2(ObjectID id){
	switch (id)
	{
	case BubbleDoor_ID:
		return doorTexture2;
		break;
	case ZebProductionPipe_ID:
		return zebpipeTexture2;
		break;
	case Player_ID:
		return playerTexture2;
		break;
	case Bullet_ID:
		return bulletTexture2;
		break;
	case Zoomer_ID:
		return zoomerTexture2;
		break;
	case Skree_ID:
		return skreeTexture2;
		break;
	case Ripper_ID:
		return ripperTexture2;
		break;
	case Zeb_ID:
		return zebTexture2;
		break;
	case Waver_ID:
		return waverTexture2;
		break;
	case Rio_ID:
		return rioTexture2;
		break;
	case ExplodeObject_ID:
		return explodeTexture2;
		break;
		//item
	case MaruMari_ID:
	case HPTonic_ID:
		return itemTexture2;
		break;

	}
};
