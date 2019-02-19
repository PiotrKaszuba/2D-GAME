#pragma once
#include "Visible.h"


// Rather linker class ; between Visible and Animated

// Attack animation requirement - vertical center of attack should be the center of picture -  it comes out of origin
// Aswell Kick animation starts from the units origin
// Attack animation height should be around 6 times lesser than whole animation height
// Attack animation width should be around 5 times lesser than whole animation width
// Attack should have atleast 2 stages with one hit interrupting opponent -effective frame value 1- and second hit knocking him back and dealing damage -value 2-
// All attack stages should be same size

// Kick animation strikes 1/8 of animation height above collision and in the animation to 1/4 of Unit collision
// It strikes from 1/4 Unit collision width and 1/5 further than collision finishes

class Sprite_Sheet :
	public Visible
{
protected:
	//width of sprite sheet
	int sprite_sheet_size;

	//a static array of animations
	Type_of_Animation sprite_sheet_animation_num[8];

    
public:
	Sprite_Sheet();
	Sprite_Sheet(int ID, Sprite_Sheet_Data data, sf::Vector2f position);
	Type_of_Animation get_sprite_sheet_animation(int animated_state);
	virtual void update(World<Physical> *mapa) = 0;
	~Sprite_Sheet();
};

