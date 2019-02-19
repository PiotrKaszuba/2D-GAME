#include "Trap.h"



Trap::Trap()
{
}

Trap::Trap(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical>* mapa) : Physical(ID, base, position, mapa)
{
	this->weight = 1;
}


void Trap::weigth2state(World<Physical> *mapa)
{
	if (weight > 1)
	{
		float x = this->getPosition().x;
		float y = this->getPosition().y;
		this->Physical_Collision(mapa);
		if (x == this->getPosition().x && y == this->getPosition().y)
			weight = 1;
	}
}

Trap::~Trap()
{
}
