#include "SpriteNumber.h"
#include"Config.h"
#include"SpriteManager.h"



SpriteNumber::SpriteNumber()
{
	Sprite::init("Data\\Sprites\\SpriteNumber\\info.simple.txt", "Data\\Sprites\\SpriteNumber\\image.png");
}

SpriteNumber* SpriteNumber::instance = 0;
SpriteNumber* SpriteNumber::getInstance()
{
	if (instance == 0)
		instance = new SpriteNumber();
	return instance;
}

SpriteNumber::~SpriteNumber()
{
}

void SpriteNumber::renderNumber(int number, int spriteIndex)
{
	D3DXMATRIX zoomMatrix;

	float zoomNumber = 0.4;

	D3DXMatrixIdentity(&zoomMatrix);
	zoomMatrix._11 = zoomNumber;
	zoomMatrix._22 = zoomNumber;

	DirectXTool::getInstance()->GetSprite()->SetTransform(&zoomMatrix);

	int actionIndex = 0;
	int frameIndex = 0;

	int frameWidth = (animations[0].frames[0].right - animations[0].frames[0].left)*zoomNumber;
	int frameHeight = (animations[0].frames[0].bottom - animations[0].frames[0].top)*zoomNumber;
	int x, y;
	y =  20 - frameHeight/2;
	if (number == 0)
	{
		frameIndex = 0;
		x = BACKBUFFER_WIDTH - 20 - frameWidth*(index++);
		Sprite::render(x / zoomNumber, y / zoomNumber, actionIndex, frameIndex);
	}
	else
	{
		while (number > 0)
		{
			frameIndex = number % 10;
			number = number / 10;
			x = BACKBUFFER_WIDTH - 20 - frameWidth*(index++);
			Sprite::render(x / zoomNumber, y / zoomNumber, actionIndex, frameIndex);
		}
	}

	index += 2;

	D3DXMatrixIdentity(&zoomMatrix);
	DirectXTool::getInstance()->GetSprite()->SetTransform(&zoomMatrix);

	auto sprite = SpriteManager::getInstance()->getSprite((SPRITE_NAME)spriteIndex);

	y = 20 - (sprite->animations[0].frames[0].bottom - sprite->animations[0].frames[0].top) / 2;

	SpriteManager::getInstance()->getSprite((SPRITE_NAME)spriteIndex)->render(BACKBUFFER_WIDTH - 30 - frameWidth*(index++), 
		
		y, 0, 0);
	index += 5;
}
