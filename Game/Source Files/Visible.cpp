#include "Visible.h"



Visible::Visible()
{
}

Visible::Visible(int ID, Sprite_Sheet_Data base, sf::Vector2f position) : Sprite(base.data) , Object(ID, base.width, base.height)
{
	this->setPosition(position);
	this->setOrigin(this->width / 2, this->height / 2);
}


Visible::~Visible()
{
}

void Visible::update(World<Physical> *mapa)
{
	mapa->draw(*this);
}

sf::Rect<int> Visible::Get_Rect()
{
	return sf::Rect<int>(this->getPosition().x-this->width/2,this->getPosition().y-this->height/2,this->width,this->height);
}

float Visible::getXpos()
{
	return this->getPosition().x;
}

float Visible::getYpos()
{
	return this->getPosition().y;
}
