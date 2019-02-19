#pragma once
#include "Projectile.h"

// shoots projectiles from Room walls
// randomly changes wall to shoot from
class Projectile_Shooter :
	public Room_Feature
{
private:
	way to_shoot;
	int number_of_projectiles;
	float projectile_damage;
	float projectile_speed;
	int index_range_start;
	Projectile **projectiles;
	bool vertical_horizontal;
public:
	Projectile_Shooter();
	Projectile_Shooter(int index_range_start, int number_of_projectiles, Sprite_Sheet_Data projectile_sample, World<Physical> *mapa, float projectile_speed = 22.f, float projectile_damage = 6);
	void update(World<Physical> *mapa);
	~Projectile_Shooter();
};

