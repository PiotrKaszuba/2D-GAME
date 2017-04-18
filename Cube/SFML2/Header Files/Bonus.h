#pragma once
#include "Enemy.h"

//enumerates types of bonuses that heal or boost stat
//0 heal
//1 regen_boost
//2 damage_boost
//3 movement_boost
enum bonus_type 
{
	heal,
	regen_boost,
	damage_boost,
	movement_boost
};

//represents objects that give player a bonus after stepping on them (usually disappear then)
class Bonus :
	public Trap
{
private:
	//used or not
	bool alive;
	//strength of bonus
	float value;
	//type of bonus
	bonus_type type;
public:
	Bonus();
	~Bonus();
	//constructor with ID, Sprite Sheet Data, position, World, bonus type, and bonus value
	Bonus(int ID, Sprite_Sheet_Data base, World<Physical> *mapa, sf::Vector2f position, bonus_type type, float value);
	//update to check if picked up, adjust position in weight=2 state
	 void update(World<Physical> *mapa);
	//effect on step, on heal activates deal_damage of picking unit with -damage, unit should take care of its max hp at its own update
	 void activate(Physical *target);
	//move away function for it
	 void deal_damage(Physical *dealer, float damage);
	//return if used or not
	 bool get_alive();

};

