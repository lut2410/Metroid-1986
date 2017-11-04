#ifndef TEXTURE_COLLECTION_H
#define TEXTURE_COLLECTION_H

#pragma once
#include "Texture.h"

class TextureCollection{
private:
	Texture* playerTexture;


	static TextureCollection* textureCollection;


public:
	TextureCollection();
	static TextureCollection* getInstance();
	~TextureCollection();
	Texture* getTexture(ObjectID id);
};
#endif