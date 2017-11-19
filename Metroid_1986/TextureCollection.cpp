#include "TextureCollection.h"
TextureCollection* TextureCollection::textureCollection = NULL;
TextureCollection::TextureCollection(){

	//playerTexture = new Texture("Resources/Image/player.png", 29, 1);
	playerTexture2 = new Texture2("Resources/Image/player/sprite.png", "Resources/Image/player/sprite.txt");
};
TextureCollection* TextureCollection::getInstance(){
	if (textureCollection == NULL)
		textureCollection = new TextureCollection();
	return textureCollection;
}
//Texture* TextureCollection::getTexture(ObjectID id){
//	switch (id)
//	{
//	case Player_ID:
//		return playerTexture;
//		break;
//	}
//}
Texture2* TextureCollection::getTexture2(ObjectID id){
	switch (id)
	{
	case Player_ID:
		return playerTexture2;
		break;
	}
};
