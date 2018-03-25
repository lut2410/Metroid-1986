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

	D3DXVECTOR3 position(x - sBox.width / 2, y - sBox.height/2, 0);
	D3DXVECTOR3 center(0, 0, 0);
	G_SpriteHandler->Draw(
		_texture2->_texture,
		&sRect,
		&center,
		&position,
		0xFFFFFFFF);
	
	//D3DXVECTOR3 inPosition(x, y, 0);
	////if (position != D3DXVECTOR3())
	////	inPosition = position;

	//D3DXVECTOR2 scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
	//D3DXMATRIX _matrix;
	//D3DXVECTOR2 _scale = D3DXVECTOR2(1, 1);
	//D3DXVECTOR2 _rotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
	//D3DXVECTOR2 _translation = D3DXVECTOR2(0, 0);
	//D3DXMatrixTransformation2D(&_matrix, &scalingCenter, 0, &_scale, &_rotationCenter, 0, &_translation);

	//D3DXMATRIX oldMatrix;
	//G_SpriteHandler->GetTransform(&oldMatrix);
	//G_SpriteHandler->SetTransform(&_matrix);
	//Box sBox = _texture2->_framePosition->at(_index);
	//RECT sRect = sBox.ToRect();
	//D3DXVECTOR3 center = D3DXVECTOR3(sBox.width / 2, sBox.height / 2, 0);

	//G_SpriteHandler->Draw(_texture2->_texture,
	//	&sRect,
	//	&center,
	//	&inPosition,
	//	D3DCOLOR_XRGB(255, 255, 255));

	//G_SpriteHandler->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
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

	this->Draw(x + sBox.width , y);

	G_SpriteHandler->SetTransform(&oldMt);
}
Box Sprite::getSpriteSize(){
	return  _texture2->_framePosition->at(_index);
	//return RECT{ -spriteSize.width / 2,	//left
	//	spriteSize.height / 2,			//top
	//	spriteSize.width / 2,			//right
	//	- spriteSize.height / 2 };		//bottom
}