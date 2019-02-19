#pragma once
#include "Projectile_Shooter.h"

// a basic unit class
// Unit is able to attack other unit, block attacks
// Unit has health and dies when it runs out of it (is removed from World)

class Unit : public Moving
{
protected:
	bool alive;
	float health;
	float max_health;
	float damage;
	float health_regen;
	sf::Text health_display;
	// a vector of power that unit is knocked back with by hit
	sf::Vector2f velocity;
	// an object that will be used on "use" action
	Physical *use_item;
public:
	Unit();
	Unit(Physical base);
	Unit(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, float speed=9.f, float health=100.f, float damage=10.f, float health_regen = 0.005f);
	~Unit();
	virtual void update(World<Physical>*mapa);
	// action start/stop; choose what action to use and set 0 to stop / 1 to start
	void start_action(state order, bool stop_start= 1);
	// an attack function that first checks if unit is attacking
	// if so; creates rectangle of your strike and checks if it collides with any Physical
	// it changes state of object or deals damage or adds velocity to an object if any possible
	// the rectangle is created from border of Unit's collision and expands in the direction (side) it is facing
	// use this in the update and pass World to it
	void attacking(World<Physical>*mapa);
	//a function handling the use action 
	// put this in the update
	void useing();
	sf::IntRect get_attack_rect(state order);
	// run this in update for when Unit is hit, it moves the unit with the acquired hit velocity
	void being_hit();
	void health_display_update(World<Physical> *mapa);
	void add_velocity(sf::Vector2f velocity);
	void set_velocity(sf::Vector2f velocity);
	void deal_damage(Physical *dealer, float damage);
	void set_use_item(Physical *item);
	float get_damage();
	void set_damage(float damage);
	bool get_alive();
	float get_health();
	float get_max_health();
	void set_max_health(float max_health);
	float get_health_regen();
	void set_health_regen(float regen);
	
	// use this in update to regen
	void regenerate();
	

};

