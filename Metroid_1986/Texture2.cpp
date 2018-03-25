#include "Texture2.h"
Texture2::Texture2(const Texture2 &texture){
	_size = texture._size;
	_texture = texture._texture;
	_animationList = texture._animationList;
}

Texture2::Texture2(char* textureFilePath, char* textFilePath){
	_LoadTexture(textureFilePath);
	if (textFilePath)
	_ImportFromTextFile(textFilePath);
}
Texture2::~Texture2(){
	if (this->_texture != NULL)
		this->_texture->Release();
}
void Texture2::_LoadTexture(char* filePath){
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(G_hWnd, filePath, "Can not load texture", MB_OK);
		return;
	}

	//RECT s = { 0, 0, info.Width, info.Height };
	_size = RECT{ 0, 0, (long) info.Width, (long) info.Height };


	result = D3DXCreateTextureFromFileEx(
		G_d3ddv,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), //color
		&info,
		NULL,
		&_texture
		);

	if (result != D3D_OK)
	{
		MessageBox(G_hWnd, filePath, "Failed to create texture from file", MB_OK);
		return;
	}

}
void Texture2::_ImportFromTextFile(char* filePath)
{
	ifstream file(filePath);
	if (!file) {
		MessageBox(G_hWnd, strcat("Cannot open file:", filePath), "Error", MB_OK);
		return;
	}
	//Read text in file

	//pretermit 3 first lines
	string line;
	getline(file, line);
	int type;		// there are 2 type: each frame are as same as, and otherwise
	int frameCount;	//amout of frame in texture
	file >> type;
	if (type)	//all frame size are equal : use for tile map
	{
		getline(file, line);
		getline(file, line);
		file >> frameCount;
		getline(file, line);
		getline(file, line);
		int cols;			//amout of frame in a row
		file >> cols;
		getline(file, line);
		getline(file, line);
		int rows;			//amout of frame in a col
		file >> rows;

		//Each frame has the same size
		int frameWidth= _size.right / cols;
		int frameHeight = _size.bottom / rows;
		//import frame detail to list
		_framePosition = new vector<Box>();
		for (int i = 0; i < frameCount; i++){
			Box box = Box{ (float) (i % cols)*frameWidth,
								(float) (i / cols)*frameHeight ,
									(float) frameWidth,
										(float) frameWidth};

			_framePosition->push_back(box);
		}
	}
	else			//each frame are different: use for objects like player,enemy,v.v.
	{
		getline(file, line);
		getline(file, line);
		file >> frameCount;
		getline(file, line);
		getline(file, line);

		//import frame detail to list
		_framePosition = new vector<Box>();
		for (int i = 0; i < frameCount; i++){
			getline(file, line);
			getline(file, line);
			getline(file, line);
			Box box;
			file >> box.x >> box.y >> box.width >> box.height;
			_framePosition->push_back(box);
			getline(file, line);
		}

		//import animation detail
		getline(file, line);
		getline(file, line);
		getline(file, line);
		_animationList = new map<string, vector<int>>();
		string animationName;				//name
		//int index[3];					//index: from, to of texture

		while (!file.eof()){
			//getline(file, line);			//animation name
			file >> animationName;
			_animationNames.push_back(animationName);
			getline(file, line);
			getline(file, line);		//2 parameter type int: from-to index
			istringstream istr_line(line);
			//istr_line >> index[0] >> index[1] >> index[2];
			vector<int> value;
			int v;
			istr_line >> v;
			value.push_back(v);
			istr_line >> v;
			value.push_back(v);
			istr_line >> v;
			value.push_back(v);
			//_animationList->insert(pair<string, int(*)[3]>(animationName,&index));
			_animationList->insert(pair<string, vector<int>>(animationName, value));
		}
	}
}

void Texture2::Draw(int x, int y){
	D3DXVECTOR3 position((float)x, (float)y, 0);
	G_SpriteHandler->Draw(_texture, &_size, NULL, &position, 0xFFFFFFFF);
}
void Texture2::Draw(int x, int y, int index){
	Box sBox = _framePosition->at(index);
	RECT sRect = sBox.ToRect();
	
	D3DXVECTOR3 position(x - sBox.width / 2, y - sBox.height / 2, 0);
	D3DXVECTOR3 center(0, 0, 0);
	G_SpriteHandler->Draw(
		_texture,
		&sRect,
		&center,
		&position,
		0xFFFFFFFF);

}
//void Texture2::Draw(int x, int y, int index){
//	D3DXVECTOR3 inPosition(x, y, 0);
//	//if (position != D3DXVECTOR3())
//	//	inPosition = position;
//
//	D3DXVECTOR2 scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
//	D3DXMATRIX _matrix;
//	D3DXVECTOR2 _scale = D3DXVECTOR2(1, 1);
//	D3DXVECTOR2 _rotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
//	D3DXVECTOR2 _translation = D3DXVECTOR2(0, 0);
//	D3DXMatrixTransformation2D(&_matrix, &scalingCenter, 0, &_scale, &_rotationCenter, 0, &_translation);
//
//	D3DXMATRIX oldMatrix;
//	G_SpriteHandler->GetTransform(&oldMatrix);
//	G_SpriteHandler->SetTransform(&_matrix);
//	Box sBox = _framePosition->at(index);
//	RECT sRect = sBox.ToRect();
//	D3DXVECTOR3 center = D3DXVECTOR3(sBox.width / 2, sBox.height / 2, 0);
//
//	G_SpriteHandler->Draw(_texture,
//		&sRect,
//		&center,
//		&inPosition,
//		D3DCOLOR_XRGB(255, 255, 255));
//
//	G_SpriteHandler->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
//}