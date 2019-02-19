#include "Projectile_Shooter.h"



Projectile_Shooter::Projectile_Shooter()
{

}

Projectile_Shooter::Projectile_Shooter(int index_range_start, int number_of_projectiles, Sprite_Sheet_Data projectile_sample, World<Physical>* mapa, float projectile_speed, float projectile_damage)
{
	this->index_range_start = index_range_start;
	this->number_of_projectiles = number_of_projectiles;
	this->projectile_speed = projectile_speed;
	this->projectile_damage = projectile_damage;
	this->to_shoot = way(rand() % 4 +1);
	this->vertical_horizontal = 1;
	int x, y;
	direction_x a = x_none;
	direction_y b = y_none;
	switch (to_shoot)
	{
	case west:
		x = 0;
		y = -1;
		a = x_right;
		break;
	case south:
		x = -1;
		y = 0;
		b = y_down;
		break;
	case east:
		x = mapa->getSize().x;
		y = -1;
		a = x_left;
		break;
	case north:
		x = -1;
		y = mapa->getSize().y;
		b = y_up;
		break;
	}

	this->projectiles = new Projectile*[this->number_of_projectiles];
	for (int i = 0; i < this->number_of_projectiles; i++)
	{
		if (to_shoot == north || to_shoot == south)
		{
			x = rand() % mapa->getSize().x;
		}
		if (to_shoot == east || to_shoot == west)
		{
			y = rand() % mapa->getSize().y;
		}
		this->projectiles[i] = new Projectile(this->index_range_start + i, projectile_sample, sf::Vector2f(x, y), mapa, this->projectile_speed, a, b, this->projectile_damage);
		this->projectiles[i]->setRotation((int(this->to_shoot) - 1) * 90);
		if (to_shoot == north || to_shoot == south)
		{
			this->vertical_horizontal = 0;
			int temp = this->projectiles[i]->Get_width();
			this->projectiles[i]->Set_width(this->projectiles[i]->Get_height());
			this->projectiles[i]->Set_height(temp);
		}
	}
}

void Projectile_Shooter::update(World<Physical>* mapa)
{
	int r = rand() % 300;
	if (r == 0)
		this->to_shoot = west;
	else if (r == 100)
		this->to_shoot = south;
	else if (r == 200)
		this->to_shoot = east;
	else if (r == 299)
		this->to_shoot = north;

	for (int i = 0; i < this->number_of_projectiles;i++)
	{
		if (this->projectiles[i]->get_alive())
		{
			this->projectiles[i]->update(mapa);
		}
		else
		{
			int x=0, y=0;
			direction_x a = x_none;
			direction_y b = y_none;
			switch (this->to_shoot)
			{
			case west:
				x = 0;
				y = rand() % mapa->getSize().y;
				a = x_right;
				break;
			case south:
				x = rand() % mapa->getSize().x;
				y = 0;
				b = y_down;
				break;
			case east:
				x = mapa->getSize().x;
				y = rand() % mapa->getSize().y;
				a = x_left;
				break;
			case north:
				x = rand() % mapa->getSize().x;
				y = mapa->getSize().y;
				b = y_up;
				break;
			}
			this->projectiles[i]->setRotation((int(this->to_shoot) - 1) * 90);
			this->projectiles[i]->set_weight(3);
			this->projectiles[i]->setPosition(sf::Vector2f(x, y));
			this->projectiles[i]->set_alive(true);
			this->projectiles[i]->set_out_of_wall(false);
			this->projectiles[i]->change_direction(a);
			this->projectiles[i]->change_direction(b);
			if ((to_shoot == north || to_shoot == south) && vertical_horizontal)
			{
				this->vertical_horizontal = 0;
				int temp = this->projectiles[i]->Get_width();
				this->projectiles[i]->Set_width(this->projectiles[i]->Get_height());
				this->projectiles[i]->Set_height(temp);
			} 
			else if ((to_shoot == east || to_shoot == west) && !vertical_horizontal)
			{
				this->vertical_horizontal = 1;
				int temp = this->projectiles[i]->Get_width();
				this->projectiles[i]->Set_width(this->projectiles[i]->Get_height());
				this->projectiles[i]->Set_height(temp);
			}
			
		}
	}

}


Projectile_Shooter::~Projectile_Shooter()
{
	for (int i = 0; i < this->number_of_projectiles; i++)
	{
		delete this->projectiles[i];
	}
	delete[] this->projectiles;
}
