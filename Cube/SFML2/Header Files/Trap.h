#pragma once
#include "Physical.h"

//this class represents a trap that might be step on to activate
//not used - base class for other traps
//it might be used for other purposes than traps - anything that activates on step
class Trap :
	public Physical
{
public:

	Trap();
	Trap(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa);
	virtual void activate(Physical *target) = 0;
	virtual void update(World<Physical> *mapa) = 0;
	//weigth2state is a state for on collision activable objects to adjust their position
	//by Physical Collision Move Away method before they can activate - get its weight back
	virtual void weigth2state(World<Physical> *mapa);
	~Trap();
};

