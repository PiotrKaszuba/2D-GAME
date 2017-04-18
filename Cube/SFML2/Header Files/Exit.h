#pragma once
#include "Usable.h"


//this represents a room exit that leads to another room
class Exit :
	public Usable
{
private:
	way to_go;
public:
	
	Exit();
	Exit(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, way to_go, int weight = 1);
	virtual void useit(Physical* user);
	~Exit();
};

