#pragma once
#include "Exit.h"

//mark for hint
//0 sum_higher
// 1 sum_lower
// 2 divisibility
// 3 does_not_contain
// 4 permutation
enum dependance
{
	sum_higher,
	sum_lower,
	divisibility,
	does_not_contain,
	permutation
};
// class representing the object that shows numeric hint on use
class Column :
	public Usable
{
private:
	dependance hint_type;
	bool hint_truth;
	char a;
	sf::Vector3<char> hint;
	sf::Text hint_display;
	int hint_lifetime;
public:
	Column();
	Column(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, bool hint_truth, sf::Vector3<char> hint, dependance hint_type);
	void useit(Physical *user);
	void update(World<Physical>*mapa);
	void hint_display_update(World<Physical>* mapa);
	~Column();
};

