#ifndef BACKGROUND_MAP_H
#define BACKGROUND_MAP_H

#include "Global Setting.h"
#include "Sprite.h"
#include "Camera.h"
#include <string>
#include <fstream>
using namespace std;
class BackgroundMap{
	int _matrixLevel;				//matrix level
	int** _mapMatrix;				//matrix
	Sprite* _mapSpr;
public:
	BackgroundMap();
	~BackgroundMap();
	void Draw(Camera*);					//Draw background map base on map matrix

};

#endif