#include "Bonus_Holder.h"



Bonus *Bonus_Holder::get_bonus()
{
	return this->bonus;
}

Bonus_Holder::Bonus_Holder()
{
	
}


Bonus_Holder::Bonus_Holder(int ID, Sprite_Sheet_Data base, World<Physical>* mapa, sf::Vector2f position, bonus_type type, float value)
{
	this->bonus = new Bonus(ID, base, mapa, position, type, value);
}

void Bonus_Holder::update(World<Physical>* mapa)
{
	this->bonus->update(mapa);
}

bool Bonus_Holder::get_alive()
{
	return this->bonus->get_alive();
}

Bonus_Holder::~Bonus_Holder()
{
}
