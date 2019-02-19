#pragma once
#include "Column.h"
// an abstract class, reprensents game/game mode
class Game
{
public:
	Game();
	//specific for each game, might show instructions, description and other stuff introducing to game
	virtual void intro(World<Physical> *mapa) = 0;
	//highest level update, usually managing game states and all objects
	virtual void update(World<Physical> *mapa) = 0;
	~Game();
};

