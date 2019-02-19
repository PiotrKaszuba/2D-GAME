#pragma once
#include "Sprite_Sheet.h"

//states that object might be in
// 0 - 4 are possible to immediately break
// 5 - 7 must finish before taking further action
// 0 still 
//1 go 
//2 block 
//3 attack 
//4 use 
//5 kick 
//6 interrupted 
//7 kick
enum state {
	still,
	go,
	block,
	attack,
	use,
	kick,
	interrupted,
	hit,
};
// right or left; which direction object faces
// 0 r
// 1 l
enum side {
	r,
	l
};

//this class represents objects that animate between frames
class Animated :
	public Sprite_Sheet
{
protected:
	//number of frame visible at a moment
	int animated_frame;
	// type of animation object is in, cast (state) to see hint and use namely
	state animated_state;
	// side object is facing, cast (side) to see hint and use namely
	side animated_side;

public:
	Animated();
	// constructor which takes unit ID, Sprite Sheet Data and position
	Animated(int ID, Sprite_Sheet_Data base, sf::Vector2f position);
	// call this (in update usually) to animate object
	void Animate();
	
	// function to put in main or engine that does all work for the object during a frame
	// put there all functions that describe what unit is able to do and update any changing data (the functions are commented to use them here)
	// it also draws the object to the World
	virtual void update(World<Physical> *mapa);
	//getter for animated state
	state get_animated_state();
	// sets to parameter state, cast (state) to use namely and see hint
	void set_animated_state(state animated_state);
	// set to a parameter frame
	void set_animated_frame(int animated_frame);
	// having it here makes it possible to set velocity to 0 after finishing animation in Animate
	virtual void set_velocity(sf::Vector2f velocity);


	
	~Animated();
};

