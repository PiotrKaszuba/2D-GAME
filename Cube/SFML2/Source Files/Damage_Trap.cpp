#include "Damage_Trap.h"



Damage_Trap::Damage_Trap()
{
}

Damage_Trap::Damage_Trap(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical>* mapa, float damage) : Trap(ID, base, position, mapa)
{
	this->damage = damage;
	//enter weight=2 state position adjusting
	this->weight = 2;
}


Damage_Trap::~Damage_Trap()
{
}

void Damage_Trap::activate(Physical *target)
{
	this->deal_damage_to(target, this->damage);
}

void Damage_Trap::deal_damage(Physical *dealer, float damage)
{
	this->Move_Away(this, dealer);
}

void Damage_Trap::update(World<Physical>* mapa)
{
	this->Animate();
	this->weigth2state(mapa);
	mapa->draw(*this);
}

void Damage_Trap::deal_damage_to(Physical * target, float damage)
{
	target->deal_damage(this, damage);
}
