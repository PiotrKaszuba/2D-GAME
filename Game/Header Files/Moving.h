#pragma once
#include "Cube.h"


// state of movement parallel to y axis
enum direction_y
{
	y_none,
	y_up,
	y_down
};

// state of movement parallel to x axis
enum direction_x
{
	x_none,
	x_left,
	x_right
};

// this class is for objects that are able to move and collide with others
class Moving :
	public Physical
{
	protected:
	float moving_speed;
	direction_y moving_direction_y;
	direction_x moving_direction_x;
public:
	Moving();
	Moving(Physical base);
	Moving(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, float speed = 5.f, direction_x x = x_none, direction_y y=y_none);
	// objects natural move
	void Move(int x, int y);
	// movement state analysis and calling move
	// use this in the update
	void Movement();
	// checks if the object stays on the screen (World) and moves it back if needed
	// use this in the update and pass World to it
	void Border_Collision(World<Physical>*mapa);
	void change_side(side kierunek);
	void change_direction(direction_x direction);
	void change_direction(direction_y direction);
	// stops performing action (0 - 3 states)
	void stop();
	virtual void update(World<Physical> *mapa);
	float get_moving_speed();
	void set_moving_speed(float speed);
	~Moving();
};

