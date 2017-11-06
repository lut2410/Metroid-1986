#include "TextureCollection.h"
TextureCollection* TextureCollection::textureCollection = NULL;
TextureCollection::TextureCollection(){
	playerTexture = new Texture("Resources/Image/playerdemo.png", 18, 1);
};
TextureCollection* TextureCollection::getInstance(){
	if (textureCollection == NULL)
		textureCollection = new TextureCollection();
	return textureCollection;
}
Texture* TextureCollection::getTexture(ObjectID id){
	switch (id)
	{
	case Player_ID:
		return playerTexture;
		break;
	}
}
