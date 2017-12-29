#include "Infor.h"
void Infor::draw(int hp)
{
	Font font =  Font(10);
	font.render("EN", 20, 20);
	font.render("--", 50, 20);
	font.render(hp, 70, 20);
}