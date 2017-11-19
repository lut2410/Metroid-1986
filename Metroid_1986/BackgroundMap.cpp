#include "BackgroundMap.h"
BackgroundMap::BackgroundMap(){
	//Load map sprite
	//Texture* mapTexture = new Texture("Resources/Image/map.png", 3, 5);
	Texture2* mapTexture = new Texture2("Resources/Image/map/sprite.png", "Resources/Image/map/sprite.txt");
	_mapSpr = new Sprite(mapTexture, -1, 0, 13);

	//Load map matrix txt
	string filePath = FILEPATH_MAPMATRIX;
	ifstream file(filePath);
	if (!file) {
		MessageBox(G_hWnd, strcat("Cannot open file:", filePath.c_str()), "Error", MB_OK);
		return;
	}

	//Read text in file

	//pretermit 3 first lines
	string line;
	getline(file, line);
	file >> _matrixLevel;
	getline(file, line);
	getline(file, line);

	//create matrix
	_mapMatrix = new int*[_matrixLevel];
	for (int i = 0; i<_matrixLevel; i++)
	{
		_mapMatrix[i] = new int[_matrixLevel];
	}

	// import to matrix use world-coordinates type
	for (int y = _matrixLevel -1 ; y >= 0; y--) {
		for (int x = 0; x < _matrixLevel; x++) {
			file >> _mapMatrix[x][y];
		}
	}

	file.close();
}
BackgroundMap::~BackgroundMap(){
	//destruct matrix
	for (int i = 0; i < _matrixLevel; i++)
		delete[] _mapMatrix[i];
	delete[] _mapMatrix;
}

void BackgroundMap::Draw(Camera* camera){
	for (int y = 0; y < _matrixLevel; y++) {
		for (int x = 0; x < _matrixLevel; x++) {
			//if value is >0 then draw, else is -1 (black) then don't draw
			if (_mapMatrix[x][y] >= 0)
			{
				D3DXVECTOR2 pos = camera->Transform(x * 16+8, y * 16+8);	//because every element has value 16x16 pixel
				_mapSpr->Draw(pos.x, pos.y, _mapMatrix[x][y]);				//+8 because passed parameter to draw is center of image
			}
		}
	}
}