#include "Unit.h"



Unit::Unit()
{
}

Unit::Unit(Physical  base) : Moving(base)
{

}

Unit::Unit(int ID,Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, float speed, float health, float damage, float health_regen) : Moving(ID, base, position, mapa, speed)
{
	this->health_display.setFont(*mapa->get_font());
	this->health_display.setScale(0.5, 0.5);
	mapa->add_obstacle(this->ID, this);
	this->health = health;
	this->max_health = health;
	this->health_regen = health_regen;
	this->damage = damage;
	velocity.x = 0;
	velocity.y = 0;
	use_item = NULL;
	this->alive = 1;
}


Unit::~Unit()
{
}

void Unit::update(World<Physical>*mapa)
{
	if (this->health > 0)
	{
		this->being_hit();
		this->Movement();
		this->attacking(mapa);
		this->useing();

		this->Border_Collision(mapa);
		this->Physical_Collision(mapa);
		this->Animate();
		
		this->regenerate();

		mapa->draw(*this);
		this->health_display_update(mapa);
	}
	else
	{
		this->alive = false;
		mapa->get_obstacle()[this->ID]->zero_collision();
	}
	
}

void Unit::start_action(state order, bool stop_start)
{
	if (stop_start)
	{
		if (this->animated_state < 5 && this->animated_state != order)
		{
			this->animated_state = order;
			this->animated_frame = 0;
		}
	}
	else if (this->animated_state == order && this->animated_state < 5)
	{
		this->stop();
	}
	
}



void Unit::attacking(World<Physical>* mapa)
{
	if (this->animated_state == attack || this->animated_state == kick)

	{
		if (this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_effective_frames()) 
		{
			if (this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_effective_frames()[this->animated_frame] != 0)
			{

				for (int i = 0;i < mapa->Get_objects();i++)
				{
					if (mapa->get_obstacle()[i]->Get_ID() != this->ID && mapa->get_obstacle()[i]->get_weight() == 2)
					{

						if (this->get_attack_rect(this->animated_state).intersects(mapa->get_obstacle()[i]->Get_Rect()))
						{
							int x = this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_effective_frames()[this->animated_frame];
							if (x == 1)
							{

								if (mapa->get_obstacle()[i]->get_animated_state() != block)

								{
									int a = 5 + x;
									mapa->get_obstacle()[i]->set_animated_state(state(a));

									mapa->get_obstacle()[i]->set_animated_frame(0);
									
									mapa->get_obstacle()[i]->deal_damage(this, this->damage / 5);
								}

							}
								
								
							if (x == 2)
							{

								if (mapa->get_obstacle()[i]->get_animated_state() != block)

								{
									int a = 5 + x;

									mapa->get_obstacle()[i]->set_animated_state(state(a));

									mapa->get_obstacle()[i]->set_animated_frame(0);

									mapa->get_obstacle()[i]->deal_damage(this, this->damage);

									mapa->get_obstacle()[i]->add_velocity(sf::Vector2f(5 + 10 * (-this->animated_side), 0));
								
								}
								else
								{

									mapa->get_obstacle()[i]->deal_damage(this, 1);

								}
									
							}
							if (x == 3)
							{
									int a = 7;

									mapa->get_obstacle()[i]->set_animated_state(state(a));

									mapa->get_obstacle()[i]->set_animated_frame(0);

									mapa->get_obstacle()[i]->deal_damage(this, this->damage*1.1);

									mapa->get_obstacle()[i]->add_velocity(sf::Vector2f(5 + 10 * (-this->animated_side), -3));

							}
						
							
								
						}
					}
				}
			}
		}
	}
}

void Unit::useing()
{
	if (this->animated_state == use)
	{
		if (this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_effective_frames())
		{
			if (this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_effective_frames()[this->animated_frame] != 0)
			{
				if (this->use_item)
				this->use_item->useit(this);
			}
		}
	}
}

sf::IntRect Unit::get_attack_rect(state order)
{
	if (order == attack)
		return sf::IntRect(this->getPosition().x + this->width  / 2 - (this->width + (this->width + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x) / 5)*this->animated_side, this->getPosition().y, (this->width + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x) / 5, (this->height + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y) / 6);
	if (order == kick)
		return sf::IntRect(this->getPosition().x + this->width / 4 - (this->width /2 + this->width / 4  + ( this->width + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x) / 5)*this->animated_side, this->getPosition().y - this->height /2 - (this->height + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y) /8, this->width / 4 + (this->width + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x) / 5, this->height/4 + (this->height + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y) / 8);
	return sf::IntRect(0, 0, 0, 0);
}


void Unit::being_hit()
{
	if (this->animated_state == hit)
	{
		this->Direct_Move(this->velocity.x, this->velocity.y);
	}
}

void Unit::health_display_update(World<Physical>* mapa)
{
	
	this->health_display.setString(std::to_string(int(this->health)));
	float a = 0;
	if (this->health >= 10) a += 8;
	if (this->health >= 100) a += 8;
	this->health_display.setPosition(this->getPosition().x - 8.f - a, this->getPosition().y - float(this->height)/2 - float(this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y)/2 - 15.f);
	mapa->draw(this->health_display);
}


void Unit::add_velocity(sf::Vector2f velocity)
{
	this->velocity += velocity;
}

void Unit::set_velocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Unit::deal_damage(Physical *dealer, float damage)
{
	this->health -= damage;
}

void Unit::set_use_item(Physical * item)
{
	this->use_item = item;
}

float Unit::get_damage()
{
	return this->damage;
}

void Unit::set_damage(float damage)
{
	this->damage = damage;
}

bool Unit::get_alive()
{
	return this->alive;
}

float Unit::get_health()
{
	return this->health;
}

float Unit::get_max_health()
{
	return this->max_health;
}
void Unit::set_max_health(float max_health)
{
	this->max_health = max_health;
}

float Unit::get_health_regen()
{
	return this->health_regen;
}

void Unit::set_health_regen(float regen)
{
	this->health_regen = regen;
}

void Unit::regenerate()
{
	if (this->health < this->max_health) {
		this->health += this->health_regen;
		if (this->health > this->max_health)
			this->health = this->max_health;
	}
}
