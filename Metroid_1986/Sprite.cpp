#include "Sprite.h"

Sprite::Sprite(){
	_texture = NULL;
	_startIndex = 0;
	_endIndex = 0;
	_timeAnimation = 0;
	_currentIndex = 0;
	_timeLocal = 0;
}
Sprite::Sprite(Texture* texture, int timeAnimation):_texture(texture){
	_startIndex = 0;
	_endIndex = _texture->_count - 1;
	_currentIndex = 0;
	_timeAnimation = timeAnimation;
	_timeLocal = 0;
}
Sprite::Sprite(Texture* texture, int timeAnimation, int startIndex, int endIndex):_texture(texture){
	_texture = texture;
	_startIndex = startIndex;
	_endIndex = endIndex;
	_currentIndex = startIndex;
	_timeAnimation = timeAnimation;
	_timeLocal = 0;
}
Sprite::~Sprite(){
	_texture->~Texture();
}
void Sprite::SelectIndex(int index){
	_currentIndex = index;
}
void Sprite::Next(){
	if (_currentIndex < _endIndex)
		_currentIndex++;
	else
		_currentIndex = _startIndex;

}
void Sprite::Update(int t){
	_timeLocal += t;
	if (_timeLocal >= _timeAnimation)
	{
		_timeLocal = 0;
		this->Next();
	}
}
void Sprite::Draw(int x, int y){


	RECT srect;

	srect.left = (_currentIndex % _texture->_cols)*(_texture->_frameWidth);
	srect.top = (_currentIndex / _texture->_cols)*(_texture->_frameHeight);
	srect.right = srect.left + _texture->_frameWidth;
	srect.bottom = srect.top + _texture->_frameHeight;

	D3DXVECTOR3 position(x - _texture->_frameWidth / 2,y - _texture->_frameHeight / 2, 0);
	D3DXVECTOR3 center(0, 0, 0);
	G_SpriteHandler->Draw(
		_texture->_texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF );
}
void Sprite::DrawFlipHorizontal(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->_frameWidth / 2, y + _texture->_frameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	x += _texture->_frameWidth;
	this->Draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}
