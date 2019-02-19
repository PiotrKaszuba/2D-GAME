#include "Usable.h"



Usable::Usable()
{
}

Usable::Usable(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical>* mapa) : Physical (ID, base, position, mapa)
{
	this->weight = 3;
}

void Usable::activate(Physical * target)
{
	target->set_use_item(this);
}


Usable::~Usable()
{
}
