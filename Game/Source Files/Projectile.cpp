#include "Projectile.h"



Projectile::Projectile()
{
}

Projectile::Projectile(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical>* mapa, float speed, direction_x x, direction_y y, float damage, bool interrupts) : Moving(ID, base, position, mapa, speed, x, y)
{
	this->damage = damage;
	this->interrupts = interrupts;
	this->alive = true;
	this->out_of_wall = false;
}


Projectile::~Projectile()
{
}

void Projectile::Direct_Move(int x, int y)
{
	if (this->out_of_wall)
	{
		this->alive = false;
		this->zero_collision();
	}
	else
	{
		this->setPosition(this->getPosition().x + x, this->getPosition().y + y);
		this->out_of_wall = true;
	}
}

void Projectile::activate(Physical * target)
{
	target->deal_damage(this, this->damage);
	if (interrupts)
	{
		target->set_animated_state((state)interrupted);
	}
	this->alive = false;
	this->zero_collision();
}

bool Projectile::get_alive()
{
	return this->alive;
}

void Projectile::set_alive(bool alive)
{
	this->alive = alive;
}

void Projectile::set_out_of_wall(bool out)
{
	this->out_of_wall = out;
}
