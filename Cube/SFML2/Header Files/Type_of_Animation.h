#pragma once
#include "World.h"


// When there is effective frames variable it has value for every frame -0 default-

// a class storing data for particular animation
// the animation should be drawn in the order : have its size (modifier) that does not collide, some start point and a regular pixel jump

class Type_of_Animation
{
private:
	//number of frames
	int type_of_animation_frames;
	//starting position at sprite sheet for first frame
	sf::Vector2i type_of_animation_start;
	//pixel offset to another frame
	sf::Vector2i type_of_animation_jump;
	// the cycle of frames after which y jump occures
	int type_of_animation_frames_loop_y_jump;
	//additional size of object in this animation (with collision size aka width, height returns total size of object in animation)
	sf::Vector2i type_of_animation_size_modifier;
	// moves animation by  minus! offset from collision
	sf::Vector2i type_of_animation_origin_modifier;
	int *type_of_animation_effective_frames;
public:
	Type_of_Animation();
	Type_of_Animation(int frames, sf::Vector2i start, sf::Vector2i jump, sf::Vector2i size_modifier, int *effective_frames = NULL, int frames_loop_y_jump = 0, sf::Vector2i origin_modifier = sf::Vector2i(0,0));
	int Get_type_of_animation_frames();
	sf::Vector2i Get_type_of_animation_start();
	sf::Vector2i Get_type_of_animation_jump();
	int Get_type_of_animation_frames_loop_y_jump();
	sf::Vector2i Get_type_of_animation_size_modifier();
	
	sf::Vector2i Get_type_of_animation_origin_modifier();
	int * Get_type_of_animation_effective_frames();
	~Type_of_Animation();
};

