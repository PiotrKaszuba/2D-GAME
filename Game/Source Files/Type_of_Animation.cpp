#include "Type_of_Animation.h"



Type_of_Animation::Type_of_Animation()
{
}

Type_of_Animation::Type_of_Animation(int frames, sf::Vector2i start, sf::Vector2i jump, sf::Vector2i size_modifier, int *effective_frames, int frames_loop_y_jump, sf::Vector2i origin_modifier)
{
	this->type_of_animation_start = start;
	this->type_of_animation_frames = frames;
	this->type_of_animation_jump=jump;
	this->type_of_animation_frames_loop_y_jump = frames_loop_y_jump;
	this->type_of_animation_size_modifier = size_modifier;
	this->type_of_animation_origin_modifier = origin_modifier;
	this->type_of_animation_effective_frames = effective_frames;
}



int Type_of_Animation::Get_type_of_animation_frames()
{
	return this->type_of_animation_frames;
}

sf::Vector2i Type_of_Animation::Get_type_of_animation_start()
{
	return this->type_of_animation_start;
}

sf::Vector2i Type_of_Animation::Get_type_of_animation_jump()
{
	return this->type_of_animation_jump;
}

int Type_of_Animation::Get_type_of_animation_frames_loop_y_jump()
{
	return this->type_of_animation_frames_loop_y_jump;
}

sf::Vector2i Type_of_Animation::Get_type_of_animation_size_modifier()
{
	return this->type_of_animation_size_modifier;
}

sf::Vector2i Type_of_Animation::Get_type_of_animation_origin_modifier()
{
	return this->type_of_animation_origin_modifier;
}

int * Type_of_Animation::Get_type_of_animation_effective_frames()
{
	return this->type_of_animation_effective_frames;
}

Type_of_Animation::~Type_of_Animation()
{
	if (this->type_of_animation_effective_frames)
	{
		//delete[]this->type_of_animation_effective_frames;
	}
}
