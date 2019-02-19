#include "Bonus.h"



Bonus::Bonus()
{
}


Bonus::~Bonus()
{
}

Bonus::Bonus(int ID, Sprite_Sheet_Data base, World<Physical>* mapa, sf::Vector2f position,  bonus_type type, float value) : Trap(ID, base, position, mapa)
{
	//enter weight=2 state position adjusting
	this->weight = 2;
	this->type = type;
	this->value = value;
	this->alive = true;
}

void Bonus::update(World<Physical>* mapa)
{
	if (this->alive)
	{
  		this->Animate();
		this->weigth2state(mapa);
		mapa->draw(*this);
	}
}

void Bonus::activate(Physical * target)
{
	if (this->alive)
	{
		this->alive = false;
		this->weight = 0;
		switch (type)
		{
		case 0:
			target->set_max_health(target->get_max_health() + value);
			target->deal_damage(this, -value);
			//std::cout << -value << " heal";
			break;
		case 1:
			target->set_health_regen(target->get_health_regen() + this->value);
			//std::cout << value << " hpreg";
			break;
		case 2:
			target->set_damage(target->get_damage() + this->value);
			//std::cout << value << " dmg";
			break;
		case 3:
			target->set_moving_speed(target->get_moving_speed() + this->value);
			//std::cout << value << " speed";
			break;
		}
	}
}

void Bonus::deal_damage(Physical * dealer, float damage)
{
	this->Move_Away(this, dealer);
}

bool Bonus::get_alive()
{
	return this->alive;
}
