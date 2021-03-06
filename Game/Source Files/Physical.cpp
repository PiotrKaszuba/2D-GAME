#include "Physical.h"






Physical::Physical()
{
}

Physical::Physical(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, int weight) : Animated(ID,base,position)
{
	this->weight = weight;
	mapa->add_obstacle(this->ID, this);
	mapa->Set_objects(1);
}

Physical::~Physical()
{
}

int Physical::get_weight()
{
	return this->weight;
}

void Physical::set_weight(int value)
{
	this->weight = value;
}


void Physical::add_velocity(sf::Vector2f velocity)
{
}

void Physical::deal_damage(Physical *dealer, float damage)
{
}

float Physical::get_damage()
{
	return 0.0f;
}

void Physical::set_damage(float damage)
{
}

void Physical::activate(Physical *target)
{
}

void Physical::set_use_item(Physical * item)
{
}

void Physical::useit(Physical * user)
{
}

void Physical::set_player_to_go(way to_go)
{
}

way Physical::get_player_to_go()
{
	return noway;
}

bool Physical::get_player_finish_used()
{
	return false;
}

bool Physical::get_player_in_menu()
{
	return false;
}

float Physical::get_health()
{
	return 0.0f;
}

void Physical::set_player_score(int change)
{
}

int Physical::get_player_score()
{
	return 0;
}

bool Physical::get_alive()
{
	return true;
}

float Physical::get_max_health()
{
	return 0.0f;
}
void Physical::set_max_health(float max_health)
{
}
float Physical::get_health_regen()
{
	return 0.0f;
}

void Physical::set_health_regen(float regen)
{
}

float Physical::get_moving_speed()
{
	return 0.0f;
}

void Physical::set_moving_speed(float speed)
{
}



void Physical::Direct_Move(int x, int y)
{
	this->setPosition(this->getPosition().x + x, this->getPosition().y + y);
	this->set_use_item(NULL);
}

void Physical::Move_Away(Physical * moved, Physical * steady)
{
	if (abs(moved->getPosition().x - steady->getPosition().x) - steady->Get_width() / 2 - moved->width / 2 > abs(moved->getPosition().y - steady->getPosition().y) - steady->Get_height() / 2 - moved->height / 2)
		if (moved->getPosition().x <= steady->getPosition().x)
		{

			moved->Direct_Move(-(moved->getPosition().x + moved->width / 2 - (steady->getPosition().x - steady->Get_width() / 2)), 0);
		}
		else
			moved->Direct_Move(-(moved->getPosition().x - moved->width / 2 - (steady->getPosition().x + steady->Get_width() / 2)), 0);

	else
		if (moved->getPosition().y <= steady->getPosition().y)
		{

			moved->Direct_Move(0, -(moved->getPosition().y + moved->height / 2 - (steady->getPosition().y - steady->Get_height() / 2)));
		}
		else
			moved->Direct_Move(0, -(moved->getPosition().y - moved->height / 2 - (steady->getPosition().y + steady->Get_height() / 2)));

}

void Physical::zero_collision()
{
	this->weight = 0;
}


void Physical::Physical_Collision(World<Physical>*mapa)
{

	for (int i = 0;i < mapa->Get_objects();i++)
	{
		if (mapa->get_obstacle()[i]->Get_ID() != this->ID) {

			if (this->Get_Rect().intersects(mapa->get_obstacle()[i]->Get_Rect()))
			{
				if (this->weight == 2 && mapa->get_obstacle()[i]->get_weight() == 2)
				{

					this->Move_Away(this, mapa->get_obstacle()[i]);

				}
				else
				{

					if (this->weight == 3 && mapa->get_obstacle()[i]->get_weight() == 2 )
					{

						this->Move_Away(this, mapa->get_obstacle()[i]);
						this->activate(mapa->get_obstacle()[i]);

					}

					if (this->weight == 2 && mapa->get_obstacle()[i]->get_weight() == 3)
					{

						this->Move_Away(this, mapa->get_obstacle()[i]);
						mapa->get_obstacle()[i]->activate(this);

					}

					if (this->weight == 3 && mapa->get_obstacle()[i]->get_weight() == 3)
					{

						this->Move_Away(this, mapa->get_obstacle()[i]);
						mapa->get_obstacle()[i]->activate(this);
						this->activate(mapa->get_obstacle()[i]);

					}

					if (this->weight == 1 && mapa->get_obstacle()[i]->get_weight() == 2)
					{
						this->activate(mapa->get_obstacle()[i]);
					}

					if (this->weight == 2 && mapa->get_obstacle()[i]->get_weight() == 1)
					{
						mapa->get_obstacle()[i]->activate(this);
					}

				}

			}
		}

	}
}