#pragma once
#include "Trap.h"

//deals damage when step on
//uses some virtual function tricks to move itself to a free spot when created with weight dependencies on Physical Collision
//it actually does activate another trap when put on but deal_damage function moves it instead of dealing damage
class Damage_Trap :
	public Trap
{
protected:
	float damage;
public:
	Damage_Trap();
	//constructor with ID, Sprite Sheet Data, position, World and damage per frame
	Damage_Trap(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, float damage = 1.75);
	~Damage_Trap();
	//activated every frame when being step on
	virtual void activate(Physical *target);
	//this function is activated when someone would deal damage to this, move away function for it
	virtual void deal_damage(Physical *dealer, float damage);
	//draws it and moves away if in state to adjust position not damage instantly when it is moved or created (weight =2 means this state)
	virtual void update(World<Physical> *mapa);
	//activates deal_damage function of object that activated trap
	void deal_damage_to(Physical* target, float damage);
	
};

