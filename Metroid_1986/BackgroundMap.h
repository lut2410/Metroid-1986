#ifndef BACKGROUND_MAP_H
#define BACKGROUND_MAP_H

#include "Global Setting.h"
#include "Sprite.h"
#include "Camera.h"
using namespace std;
//To Draw Background Map - (ground-static object)
class BackgroundMap{
	int _matrixLevel;				//matrix level
	int** _mapMatrix;				//matrix
	Texture2* _mapTexture;
public:
	BackgroundMap();
	~BackgroundMap();
	void Draw(Camera*);					//Draw background map base on map matrix

};

#endif