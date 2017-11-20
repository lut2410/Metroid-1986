#include "Sprite.h"

Sprite::Sprite(){
	_texture2 = NULL;
	_index = 0;
}
Sprite::Sprite(Texture2* texture, int index) :_texture2(texture){
	_index = index;
}

Sprite::~Sprite(){
}


void Sprite::Draw(int x, int y){

	Box sBox = _texture2->_framePosition->at(_index);
	RECT sRect = sBox.ToRect();

	D3DXVECTOR3 position(x - sBox.width / 2, y - sBox.height / 2, 0);
	D3DXVECTOR3 center(0, 0, 0);
	G_SpriteHandler->Draw(
		_texture2->_texture,
		&sRect,
		&center,
		&position,
		0xFFFFFFFF);
}
void Sprite::DrawFlipHorizontal(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	Box sBox = _texture2->_framePosition->at(_index);
	D3DXVECTOR2 center = D3DXVECTOR2(x + sBox.width / 2, y + sBox.height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	x += sBox.width;
	this->Draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}