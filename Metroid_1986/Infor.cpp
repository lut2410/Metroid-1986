#include "Infor.h"
Animation* Infor::_currentArmedAnimation = NULL;
Animation* Infor::_rocketAnimation = NULL;
Infor::Infor(){
	Texture2* bulletTexture = NULL;
	bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
	_rocketAnimation = new Animation(bulletTexture, "Rocket:Top");
	//_rocketAnimation = a;
	_currentArmedAnimation = new Animation(bulletTexture, "Normal:Flying");
}
void Infor::switchToOtherBulletType(BulletType bulletType)
{
	Texture2* bulletTexture = NULL;
	bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
	switch (bulletType)
	{
	case BulletType::BulletFromPlayer_Nomal:
		_currentArmedAnimation = new Animation(bulletTexture, "Normal:Flying");
		break;
	case BulletType::BulletFromPlayer_Freeze:
		_currentArmedAnimation = new Animation(bulletTexture, "Freeze:Flying");
		break;
	case BulletType::BulletFromPlayer_Wave:
		_currentArmedAnimation = new Animation(bulletTexture, "Wave");
		break;
	case BulletType::BulletFromPlayer_Rocket:
		_currentArmedAnimation = new Animation(bulletTexture, "Rocket:Right");
		break;
	}

	


}
void Infor::draw(int hp, int rocketnumber)
{
	Font font =  Font(10);
	font.onLost();
	font.render("EN", 20, 20);
	font.render("--", 50, 20);
	font.render(hp, 70, 20);

	//draw rocket number
	_rocketAnimation->Draw(20,50);
	font.render(rocketnumber, 70, 50);
	_currentArmedAnimation->Draw(20, 80);


}