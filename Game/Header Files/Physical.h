#pragma once
#pragma once
#include "Animated.h"

class Unit;
enum way
{
	noway,
	east,
	north,
	west,
	south,
	upstairs,
	downstairs
};

// represents objects that might collide with others
// constructor adds the object to World's array of objects that checks for collision
// weight value:
// 0 - passing object that does not activate pass effects and is passable
// 1 - effect on passing object, does not activate pass effects and is with effect passable
// 2 - non-passing object that does activate pass effects and is non-passable
// 3 - non passing object that does activate pass effects and is non-passable with effect when being tried to pass
//  collision  cases:
// 0 - 0 , 0 - 1, 1 - 0, 1 - 1, 0 - 2, 2 - 0, 3 - 0, 0 - 3, - pass
// 1 - 2, 2 - 1, 1 - 3, 3 - 1 - activates effect (of 1) and pass
// 2 - 2, - does not pass
// 2-3, 3 - 2, 3 - 3 - does not pass and activate effect (of 3)
class Physical :
	public Animated
{
protected:
	// 0 - passing object that does not activate pass effects and is passable
	// 1 - effect on passing object, does not activate pass effects and is with effect passable
	// 2 - non-passing object that does activate pass effects and is non-passable
	// 3 - non passing object that does activate pass effects and is non-passable with effect when being tried to pass
	//  collision  cases:
	// 0 - 0 , 0 - 1, 1 - 0, 1 - 1, 0 - 2, 2 - 0, 3 - 0, 0 - 3, - pass
	// 1 - 2, 2 - 1, 1 - 3, 3 - 1 - activates effect (of 1) and pass
	// 2 - 2, - does not pass
	// 2-3, 3 - 2, 3 - 3 - does not pass and activate effect (of 3)
	int weight;
public:
	Physical();
	Physical(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, int weight = 2);
	virtual ~Physical();
	int get_weight();
	void set_weight(int value);
	// those virtuals make it possible to use Unit values from Physical class (World is for Physical in default)
	virtual void add_velocity(sf::Vector2f velocity);
	virtual void deal_damage(Physical *dealer, float damage);
	virtual float get_damage();
	virtual void set_damage(float damage);
	virtual void activate(Physical *target);
	virtual void set_use_item(Physical *item);
	virtual void useit(Physical *user);
	virtual void set_player_to_go(way to_go);
	virtual way get_player_to_go();
	virtual bool get_player_finish_used();
	virtual bool get_player_in_menu();
	virtual float get_health();
	virtual void set_player_score(int change);
	virtual int get_player_score();
	virtual bool get_alive();
	virtual float get_max_health();
	virtual void set_max_health(float max_health);
	virtual float get_health_regen();
	virtual void set_health_regen(float regen);
	virtual float get_moving_speed();
	virtual void set_moving_speed(float speed);
	// checks if the objects collides with a Physical and moves it back if needed
	// use this in the update(here, in Physical it's not useful, start from Moving and Trap) and pass World to it
	void Physical_Collision(World<Physical> *mapa);
	// moved (back) by collision or knocked by other sources
	virtual void Direct_Move(int x, int y);
	// puts the moved object outside steady object
	void Move_Away(Physical *moved, Physical *steady);
	// changes weight to 0
	virtual void zero_collision();

	
};



