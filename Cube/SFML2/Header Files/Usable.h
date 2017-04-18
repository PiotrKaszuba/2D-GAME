#pragma once
#include "Damage_Trap_Spreader.h"


//An abstract class that is an object able to be used by Unit after colliding with it
class Usable :
	public Physical
{
public:
	Usable();
	Usable(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa);

	virtual void activate(Physical *target);
	void useit(Physical *user) = 0;


	~Usable();
};

