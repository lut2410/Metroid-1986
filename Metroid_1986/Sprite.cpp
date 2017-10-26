#include "Sprite.h"

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, char *Path, int Width, int Height,
	int Count, int SpritePerRow){
	D3DXIMAGE_INFO info;
	HRESULT result;
	_Index = 0;
	_Image = NULL;
	_SpriteHandler = SpriteHandler;
	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	//result = D3DXGetImageInfoFromFile(Path, &info);
	//LPDIRECT3DDEVICE9 d3ddv;
	//SpriteHandler->GetDevice(&d3ddv);
	//result = D3DXCreateTextureFromFileEx(d3ddv, Path,
	//	info.Width, info.Height,
	//	1, D3DUSAGE_DYNAMIC,
	//	D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
	//	D3DX_DEFAULT, D3DX_DEFAULT,
	//	D3DCOLOR_XRGB(0, 0, 0),	//black background
	//	&info, NULL, &_Image);
}
void Sprite::Next(){
	if (_Index < _Count)
		_Index += 1;
	else
		_Index = 0;

}
void Sprite::Render(int x, int y){
	RECT srect;
	srect.left = (_Index % _SpritePerRow)*(_Width);
	srect.top = (_Index / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width - 1;
	srect.bottom = srect.top + _Height - 1;
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 postion((float)x, (float)y, 0);//k dung d3dxvector2?
	_SpriteHandler->Draw(_Image//draw to image
		, &srect//rect position in source
		, NULL, &postion//dest position
		, D3DCOLOR_XRGB(255, 255, 255));
	_SpriteHandler->End();
}
