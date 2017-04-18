#include "Exit.h"



Exit::Exit()
{
}

Exit::Exit(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical>* mapa, way to_go, int weight) : Usable(ID, base, position, mapa)
{
	this->to_go = to_go;
	this->weight = weight;
}


void Exit::useit(Physical * user)
{
	user->set_player_to_go(this->to_go);
}



Exit::~Exit()
{
}