#include "Texture2.h"
Texture2::Texture2(const Texture2 &texture){
	_size = texture._size;
	_texture = texture._texture;
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
	_size = RECT{ 0, 0, info.Width, info.Height };


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
	file >> type;
	if (type)	//all frame size are equal
	{
		getline(file, line);
		getline(file, line);
		file >> _frameCount;
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
		for (int i = 0; i < _frameCount; i++){
			Box box = Box{ (float) (i % cols)*frameWidth,
								(float) (i / cols)*frameHeight ,
									(float) frameWidth,
										(float) frameWidth};

			_framePosition->push_back(box);
		}
	}
	else			//each frame are different
	{
		getline(file, line);
		getline(file, line);
		file >> _frameCount;
		getline(file, line);
		getline(file, line);

		//import frame detail to list
		_framePosition = new vector<Box>();
		for (int i = 0; i < _frameCount; i++){
			getline(file, line);
			getline(file, line);
			getline(file, line);
			getline(file, line);
			getline(file, line);
			getline(file, line);
			getline(file, line);
			getline(file, line);
			getline(file, line);
			Box box;
			file >> box.x >> box.y >> box.width >> box.height;
			_framePosition->push_back(box);
			getline(file, line);
			getline(file, line);
		}
	}
	
}
void Texture2::Draw(int x, int y){
	D3DXVECTOR3 position((float)x, (float)y, 0);
	G_SpriteHandler->Draw(_texture, &_size, NULL, &position, 0xFFFFFFFF);
}