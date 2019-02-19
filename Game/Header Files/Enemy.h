#pragma once
#include "Unit.h"

//stores relation of player position to enemy by x axis
//says if player is in collision by dimension x, close to left or right or further
//0 equalx
//1 totheleft
//2 totheright
//3 closeleft
//4 closeright
enum positionx
{
	equalx,
	totheleft,
	totheright,
	closeleft,
	closeright
};
//stores relation of player position to enemy by y axis
//says if player is in collision by dimension y, close higher or lower or further
//0 equaly
//1 higher
//2 lower
//3 closehigher
//4 close lower
enum positiony
{
	equaly,
	higher,
	lower,
	closehigher,
	closelower
};
// AI for computer enemy
class Enemy :
	public Room_Feature
{
private:
	//unit for enemy
	Unit *enemy;
	int *order_efficiency;
public:
	Enemy();
	//constructor which takes object ID, Sprite Sheet Data, World, enemy position and health
	Enemy(int index, Sprite_Sheet_Data unit_sample, World<Physical> *mapa, sf::Vector2f position, float health = 100.f, float damage = 10.f, float movement=9.f, float regen=0.005);
	//update of AI and unit
	void update(World<Physical> *mapa);
	Unit *get_enemy();
	//function to read position relation by x
	positionx scan_positionx(Physical *opponent);
	//function to read position relation by y
	positiony scan_positiony(Physical * opponent);
	//used in update, its AI decision making
	void order(Physical *opponent);
	float get_health();
	 bool get_alive();

	 float getXpos();
	 float getYpos();
	 int Get_ID();
	~Enemy();
};

