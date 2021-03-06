#pragma once
#include "Room_Feature.h"

enum trap_shape
{
	random,
	circle
};
// spreads Damage_Traps around the Room
// traps naturally put themselves separated
// Spreader avoids putting a trap on another object, it might place it on edge which will happen quite frequently
// due to the system of avoiding the initial collision. Player will often unexpectedly walk into one
struct Damage_Trap_Info
{
	Damage_Trap *trap;
	int time_left;
};

class Damage_Trap_Spreader :
	public Room_Feature
{
protected:
	trap_shape shape;
	Damage_Trap_Info *traps;
	float trap_damage;
	int number_of_traps;
	int trap_lifetime;
	int index_range_start;
	sf::Vector2i center;
	float radius;
public:
	Damage_Trap_Spreader();
	Damage_Trap_Spreader(int index_range_start, int number_of_traps, Sprite_Sheet_Data trap_sample, World<Physical> *mapa, int trap_lifetime = 160, float trap_damage = 1.75f);

	~Damage_Trap_Spreader();
	void update(World<Physical> *mapa);
};

