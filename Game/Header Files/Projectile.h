#pragma once
#include "Moving.h"

// this class is for bolts - objects that move and collide with effect (damage effect base)
class Projectile :
	public Moving
{
protected:
	float damage;
	bool interrupts;
	bool alive;
	bool out_of_wall;

public:
	Projectile();
	Projectile(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, float speed = 15.f, direction_x x = x_none, direction_y y = y_none, float damage = 7.f, bool interrupts = true);
	~Projectile();
	void Direct_Move(int x, int y);
    void activate(Physical *target);
	bool get_alive();
	void set_alive(bool alive);
	void set_out_of_wall(bool out);
	
};

