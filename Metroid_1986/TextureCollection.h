#ifndef TEXTURE_COLLECTION_H
#define TEXTURE_COLLECTION_H

#pragma once
#include "Texture.h"
#include "Texture2.h"
class TextureCollection{
private:
	//Texture* playerTexture;
	Texture2* playerTexture2;
	static TextureCollection* textureCollection;


public:
	TextureCollection();
	static TextureCollection* getInstance();
	~TextureCollection();
	//Texture* getTexture(ObjectID id);
	Texture2* getTexture2(ObjectID id);
};
#endif