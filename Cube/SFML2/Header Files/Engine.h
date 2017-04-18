#pragma once
#include "Player.h"
// this class runs the game in an infinite loop and handles events
// it needs World, Player created in this World with index 0 and then Game also created in this World to run properly
class Engine
{
private:
	//keeps chosen game rules
	Game *game;
	//keeps world the game takes place in (screen, objects)
	World<Physical> *mapa;
public:
	Engine();
	//constructor which takes Game and World
	Engine(Game *game, World<Physical> *mapa);
	//starts the Game
	void run();
	~Engine();
};

