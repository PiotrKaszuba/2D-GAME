#include "Animated.h"



Animated::Animated() 
{

}


Animated::Animated(int ID, Sprite_Sheet_Data base, sf::Vector2f position) : Sprite_Sheet(ID,base, position)
{
	this->animated_frame = 0;
	this->animated_side = r;
	this->animated_state = still;
	this->setOrigin((this->width + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x) / 2 + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_origin_modifier().x, (this->height + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y) / 2 + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_origin_modifier().y);
	

}

void Animated::Animate()
{
	if (this->animated_frame < this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_frames()-1)
		this->animated_frame++;
	else
	{
		if (this->animated_state > 3)
		{
			this->animated_state = still;
			this->set_velocity(sf::Vector2f(0, 0));
		}
		this->animated_frame = 0;
	}
	int v = this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_frames_loop_y_jump();
	if (v == 0) v = 1;
	int x = this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_start().x + (this->animated_frame - (this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_frames_loop_y_jump()*(this->animated_frame/v)))*this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_jump().x;
	int y = this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_start().y + (this->animated_frame / v)*this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_jump().y;
	if (this->animated_side == l)
	{
		x = this->sprite_sheet_size - x - (this->width + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x);
	}

	this->setTextureRect(sf::IntRect(x, y, this->width+this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x, this->height + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y));
	this->setOrigin((this->width + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().x) / 2 + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_origin_modifier().x, (this->height + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y) / 2 + this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_origin_modifier().y);

}

void Animated::update(World<Physical> *mapa)
{
	this->Animate();
	mapa->draw(*this);
	
}

state Animated::get_animated_state()
{
	return this->animated_state;
}

void Animated::set_animated_state(state animated_state)
{
	if (this->sprite_sheet_animation_num[animated_state].Get_type_of_animation_frames() > 0)
	this->animated_state = animated_state;
}

void Animated::set_animated_frame(int animated_frame)
{
	this->animated_frame = animated_frame;

}

void Animated::set_velocity(sf::Vector2f velocity)
{
}


Animated::~Animated()
{
}
