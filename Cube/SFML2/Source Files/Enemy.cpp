#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(int index, Sprite_Sheet_Data unit_sample, World<Physical>* mapa, sf::Vector2f position, float health, float damage, float movement, float regen)
{
	this->enemy = new Unit(index, unit_sample, position, mapa, movement, health, damage, regen);
	this->order_efficiency = new int[4];
}

void Enemy::update(World<Physical>* mapa)
{
	this->order(mapa->get_obstacle()[0]);
	this->enemy->update(mapa);
}

Unit *Enemy::get_enemy()
{
	return enemy;
}

positionx Enemy::scan_positionx(Physical *opponent)
{

	int a = this->enemy->getPosition().x - opponent->getPosition().x;
	if (abs(a) < this->enemy->Get_width() / 2 + opponent->Get_width() / 2)
		return equalx;
	else 
		if (a > 0)
		if (a <= this->enemy->Get_width() / 2 + opponent->Get_width() / 2 + this->enemy->Get_width() / 5)
			return closeright;
		else
			return totheright;
	else
		if (a >= -(this->enemy->Get_width() / 2 + opponent->Get_width() / 2 )-this->enemy->Get_width() / 5)
			return closeright;
		else
			return totheleft;
}

positiony Enemy::scan_positiony(Physical *opponent)
{

	int a = this->enemy->getPosition().y - opponent->getPosition().y;
	if (abs(a) < this->enemy->Get_height() / 2 + opponent->Get_height() / 2)
		return equaly;
	else if (a > 0)
			if (a <= this->enemy->Get_height() / 2 + opponent->Get_height() / 2 + (this->enemy->Get_height() + this->enemy->get_sprite_sheet_animation(this->enemy->get_animated_state()).Get_type_of_animation_size_modifier().y)/8)
				return closelower;
			else
				return lower;
		else
			if (a >= -(this->enemy->Get_height() / 2 + opponent->Get_height() / 2 + (this->enemy->Get_height() + this->enemy->get_sprite_sheet_animation(this->enemy->get_animated_state()).Get_type_of_animation_size_modifier().y) / 8)
				)
				return closehigher;
			else
				return higher;
}

void Enemy::order(Physical *opponent)
{
	positionx x = this->scan_positionx(opponent);
	positiony y = this->scan_positiony(opponent);

	switch (x)
	{
	case equalx:
		this->enemy->change_direction(x_none);
		break;
	case totheleft:
		this->enemy->change_direction(x_right);
		break;
	case totheright:
		this->enemy->change_direction(x_left);
		break;

	}

	switch (y)
	{
	case equaly:
		this->enemy->change_direction(y_none);
		break;
	case higher:
		this->enemy->change_direction(y_down);
		break;
	case lower:
		this->enemy->change_direction(y_up);
		break;

	}
	int ra = rand() % 30;
	if (((x == closeleft || x == closeright) && y == equaly) || ra == 0 )
	{
		if (opponent->get_animated_state() == block || opponent->get_animated_state() == attack)
		{
			
			if (opponent->get_animated_state() == attack)
			{
				if (x == closeleft)
					this->enemy->change_direction(x_left);
				else this->enemy->change_direction(x_right);
			}
			if (this->enemy->getPosition().y - opponent->getPosition().y > 0)
				this->enemy->change_direction(y_down);
			else this->enemy->change_direction(y_up);
		}
		else
		this->enemy->start_action(attack, 1);
	}
	if (((x == closeleft || x == closeright) && y == closelower ) || ra == 1)
	{
		this->enemy->start_action(kick, 1);
	}
	if ((y == closehigher && (x == closeleft || x == closeright)) || ra == 2)
	{
		this->enemy->change_direction(y_down);
		
	}
	if (((y == closehigher || y == closelower) && x == equalx)|| ra == 3)
	{
		if (this->enemy->getPosition().x - opponent->getPosition().x > 0)
			this->enemy->change_direction(x_right);
		else this->enemy->change_direction(x_left);
	}
	if ((y == closehigher && opponent->get_animated_state() == kick)|| ra==4)
	{
		this->enemy->change_direction(y_up);
		if (x == closeleft)
			this->enemy->change_direction(x_left);
		else  if (x == closeright) this->enemy->change_direction(x_right);
	}
}

float Enemy::get_health()
{
	return this->enemy->get_health();
}

bool Enemy::get_alive()
{
	return this->enemy->get_alive();
}

float Enemy::getXpos()
{
	return this->enemy->getXpos();
}

float Enemy::getYpos()
{
	return this->enemy->getYpos();
}

int Enemy::Get_ID()
{
	return this->enemy->Get_ID();
}


Enemy::~Enemy()
{
	delete[] this->order_efficiency;
	delete this->enemy;
}
