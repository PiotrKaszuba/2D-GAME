#include "Sprite_Sheet.h"


Sprite_Sheet::Sprite_Sheet()
{

}

Sprite_Sheet::Sprite_Sheet(int ID, Sprite_Sheet_Data data, sf::Vector2f position) : Visible(ID, data, position)
{
	this->sprite_sheet_size = data.size;
	this->sprite_sheet_animation_num[0] = data.still;
	this->sprite_sheet_animation_num[1] = data.go;
	this->sprite_sheet_animation_num[2] = data.block;
	this->sprite_sheet_animation_num[3] = data.attack;
	this->sprite_sheet_animation_num[4] = data.use;
	this->sprite_sheet_animation_num[5] = data.kick;
	this->sprite_sheet_animation_num[6] = data.interrupted;
	this->sprite_sheet_animation_num[7] = data.hit;
	
}

Type_of_Animation Sprite_Sheet::get_sprite_sheet_animation(int animated_state)
{

	return this->sprite_sheet_animation_num[animated_state];
}

Sprite_Sheet::~Sprite_Sheet()
{
}
