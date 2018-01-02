#ifndef TEXTURE_COLLECTION_H
#define TEXTURE_COLLECTION_H

#pragma once
#include "Texture2.h"
class TextureCollection{
private:
	Texture2* doorTexture2;
	Texture2* zebpipeTexture2;
	Texture2* playerTexture2;
	Texture2* bulletTexture2;
	//enemy
	Texture2* explodeTexture2;
	Texture2* zoomerTexture2;
	Texture2* skreeTexture2;
	Texture2* ripperTexture2;
	Texture2* zebTexture2;
	Texture2* waverTexture2;
	Texture2* rioTexture2;
	//boss
	Texture2* ridleyTexture2;
	//item
	Texture2* itemTexture2;
	static TextureCollection* textureCollection;


public:
	TextureCollection();
	static TextureCollection* getInstance();
	~TextureCollection();
	//Texture* getTexture(ObjectID id);
	Texture2* getTexture2(ObjectID id);
};
#endif