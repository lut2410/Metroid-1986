#include "Texture.h"

Texture::Texture(){

}
Texture::Texture(char* filePath, int cols, int rows)
{
	_filePath = filePath;
	_cols = cols;
	_rows = rows;
	LoadTexture();
}
Texture::~Texture()
{
	if (this->_texture != NULL)
		this->_texture->Release();
}
void Texture::LoadTexture(){
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(_filePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(G_hWnd, _filePath, "Can not load texture", MB_OK);
		return;
	}

	RECT s = { 0, 0, info.Width, info.Height };
	this->_size = s;

	_frameWidth = info.Width / _cols;
	_frameHeight = info.Height / _rows;

	

	result = D3DXCreateTextureFromFileEx(
		G_d3ddv,
		_filePath,
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
		MessageBox(G_hWnd, _filePath, "Failed to create texture from file", MB_OK);
		return;
	}
}
void Texture::Draw(int x, int y){
	D3DXVECTOR3 position((float)x, (float)y, 0);
	G_SpriteHandler->Draw(_texture, &_size, NULL, &position, 0xFFFFFFFF);
}