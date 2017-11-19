#include "Sprite.h"

Sprite::Sprite(){
	_texture2 = NULL;
	_startIndex = 0;
	_endIndex = 0;
	_timeAnimation = 0;
	_currentIndex = 0;
	_timeLocal = 0;
}
Sprite::Sprite(Texture2* texture, int timeAnimation):_texture2(texture){
	_startIndex = 0;
	_endIndex = _texture2->_frameCount - 1;
	_currentIndex = 0;
	_timeAnimation = timeAnimation;
	_timeLocal = 0;
}

Sprite::Sprite(Texture2* texture2, int timeAnimation, int startIndex, int endIndex) :_texture2(texture2){
	_texture2 = texture2;
	_startIndex = startIndex;
	_endIndex = endIndex;
	_currentIndex = startIndex;
	_timeAnimation = timeAnimation;
	_timeLocal = 0;
}
Sprite::~Sprite(){
	_texture2->~Texture2();
}
void Sprite::SelectIndex(int index){
	_currentIndex = index;
}
int Sprite::getCurrentIndex(){
	return _currentIndex;
}
void Sprite::Next(){
	if (_currentIndex < _endIndex)
		_currentIndex++;
	else
		_currentIndex = _startIndex;

}
void Sprite::Update(int t){
	if (_timeAnimation < 0)//no update
		return;
	_timeLocal += t;
	if (_timeLocal >= _timeAnimation)
	{
		_timeLocal = 0;
		this->Next();
	}
}

void Sprite::Draw(int x, int y, int index){
		_currentIndex = index;

	Box sBox = _texture2->_framePosition->at(_currentIndex);
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
void Sprite::Draw(int x, int y){
	//Get location of frame in texture
	Box sBox = _texture2->_framePosition->at(_currentIndex);
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
	Box sBox = _texture2->_framePosition->at(_currentIndex);
	D3DXVECTOR2 center = D3DXVECTOR2(x + sBox.width / 2, y + sBox.height / 2 );
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	x += sBox.width;
	this->Draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}
