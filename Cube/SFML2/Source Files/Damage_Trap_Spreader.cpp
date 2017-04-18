#include "Damage_Trap_Spreader.h"



Damage_Trap_Spreader::Damage_Trap_Spreader()
{
}

Damage_Trap_Spreader::Damage_Trap_Spreader(int index_range_start, int number_of_traps, Sprite_Sheet_Data trap_sample, World<Physical> *mapa, int trap_lifetime, float trap_damage) : Room_Feature()
{
	this->shape = circle;
	this->center = sf::Vector2i(mapa->getSize().x/2, mapa->getSize().y/2);
	this->radius = sqrt(pow(trap_sample.width, 2) + pow(trap_sample.height, 2))*number_of_traps / 6.28;
	this->index_range_start = index_range_start;
	this->number_of_traps = number_of_traps;
	this->trap_lifetime = trap_lifetime;
	this->trap_damage = trap_damage;
	
	this->traps = new Damage_Trap_Info[this->number_of_traps];
	for (int i = 0; i < this->number_of_traps;i++)
	{
		this->traps[i].trap = new Damage_Trap(i+this->index_range_start, trap_sample, sf::Vector2f(float(rand() % mapa->getSize().x + mapa->Get_border_size().x / 2), float(rand() % mapa->getSize().y + mapa->Get_border_size().y / 2)), mapa, this->trap_damage);
		this->traps[i].time_left = rand() % this->trap_lifetime;
	}
}


Damage_Trap_Spreader::~Damage_Trap_Spreader()
{
	for (int i = 0; i < this->number_of_traps;i++)
	{
		delete this->traps[i].trap;
	}
	delete[] this->traps;

}

void Damage_Trap_Spreader::update(World<Physical>* mapa)
{
	
	int x = rand() % 200;
	if (x == 0)
	{
		this->shape = random;

	}
	if (x == 199)
	{
		this->shape = circle;

	}
	for (int i = 0; i < number_of_traps;i++)
	{
		if (this->traps[i].time_left == 0)
		{

		if (this->shape == random)
			this->traps[i].trap->setPosition(sf::Vector2f(float(rand() % mapa->getSize().x + mapa->Get_border_size().x / 2), float(rand() % mapa->getSize().y + mapa->Get_border_size().y / 2)));
			
		if (this->shape == circle)
		{
			float x = this->center.x ;
			/*
			int z=1;
			if (i < this->number_of_traps / 2)
			{
				
				x -= (this->radius / (this->number_of_traps / 4)) * (i%(this->number_of_traps/2) - (this->number_of_traps / 4)) +0.02;
				if (i % (number_of_traps / 2) == 1)
				{
					x += this->radius /( this->number_of_traps / 2);
				}
				else
				if (i % (number_of_traps / 2) == this->number_of_traps/2 - 1)
				{
					x -= this->radius /( this->number_of_traps / 2);
				}
			}
			else
			{
				x += (this->radius / (this->number_of_traps / 4)) * (i%(this->number_of_traps/2) - (this->number_of_traps / 4)) + 0.02;
				z = 2;
				if (i % (number_of_traps / 2) == 1)
				{
					x -= this->radius / (this->number_of_traps / 2);
				}
				else
				if (i % (number_of_traps / 2) == this->number_of_traps/2 - 1)
				{
					x += this->radius / (this->number_of_traps / 2);
				}
			}
		
			float y = float(solve_square_equation(1, -2 * this->center.y, -pow(this->radius, 2) + pow(x, 2) + pow(this->center.x, 2) + pow(this->center.y, 2) - 2 * x*this->center.x, z));
		*/
			
			float y = this->center.y;
			x += this->radius * cos(2 * M_PI / this->number_of_traps * i);
			y += this->radius * sin(2 * M_PI / this->number_of_traps * i);
			
			this->traps[i].trap->setPosition(sf::Vector2f(x, y));

		} 
			this->traps[i].time_left = this->trap_lifetime / 2 + rand() % this->trap_lifetime / 2;
			this->traps[i].trap->set_weight(2);
		}
		this->traps[i].trap->update(mapa);
		this->traps[i].time_left -= 1;
	}
}
