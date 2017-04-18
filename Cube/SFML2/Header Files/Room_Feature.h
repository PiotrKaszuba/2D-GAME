#pragma once
#include "Damage_Trap.h"

// an abstract class of Room configuration control
class Room_Feature
{
public:
	Room_Feature();
	virtual void update(World<Physical> *mapa) = 0;
	virtual bool get_alive();
	virtual float get_health();
	virtual float getXpos();
	virtual float getYpos();
	virtual int Get_ID();
	virtual ~Room_Feature();
};

