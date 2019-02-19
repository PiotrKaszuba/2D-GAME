#pragma once
#include "Bonus.h"

//class used to be a container for Room Feature Bonus
class Bonus_Holder :
	public Room_Feature
{
private:
	//holds Bonus
	Bonus *bonus;
public:
	Bonus *get_bonus();
	//constructor made of Bonus
	Bonus_Holder(int ID, Sprite_Sheet_Data base, World<Physical> *mapa, sf::Vector2f position, bonus_type type, float value);
	void update(World<Physical> *mapa);
    bool get_alive();
	Bonus_Holder();
	~Bonus_Holder();
};

