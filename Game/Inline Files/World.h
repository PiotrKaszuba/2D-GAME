#pragma once
#include "Const values.h"


// This class might be called "Map". After being a Window, it stores what is in a game location:
// Available area, pointers to objects
// from a basic class and higher level (default Physical)(template)
// and number of objects at max (although dynamic, limited array size)
// because its template it is all written in .h file

template <class x>
class World : public sf::RenderWindow
{
protected:
	sf::Vector2<int> border_size;
	sf::Font font;
	x **obstacle;
	int max_objects;
	int objects;

	
public:
	World();
	World(sf::Vector2i size, sf::Vector2i border_size, int objects);
	~World();
	//those 2 return x & y dimensions of playable terrain (discluding borders)
	int Get_width();
	int Get_height();
	sf::Vector2i Get_border_size();
	int Get_max_objects();
	// use this to change number of objects by any integer (substract possible)
    void Set_objects(int change);
    int Get_objects();
	// use this to get or change data in the array of an object by ID
	x **get_obstacle();
	// adds new object to an array
    void add_obstacle(int ID, x*);
	sf::Font *get_font();

};


template <class x>
World<x>::World()
{
}
template <class x>
World<x>::World(sf::Vector2i size, sf::Vector2i border_size, int objects) : RenderWindow(sf::VideoMode(size.x+border_size.x,size.y+border_size.y), "Cube")
{
	this->border_size = border_size;
	this->obstacle = new x*[objects];
	this->max_objects = objects;
	this->objects = 0;
	this->font.loadFromFile(name_font_blazed);
	for (int i = 0; i < this->max_objects;i++)
	{
		this->obstacle[i] = NULL;
	}
}

template <class x>
World<x>::~World()
{
	delete[] this->obstacle;
}
template <class x>
int World<x>::Get_width()
{
	return this->getSize().x - this->border_size.x;
}
template <class x>
int World<x>::Get_height()
{
	return this->getSize().y - this->border_size.y;
}

template<class x>
inline sf::Vector2i World<x>::Get_border_size()
{
	return this->border_size;
}

template<class x>
inline int World<x>::Get_max_objects()
{
	return max_objects;
}

template<class x>
inline void World<x>::Set_objects(int change)
{
	objects += change;
}

template<class x>
inline int World<x>::Get_objects()
{
	return objects;
}

template <class x>
x **World<x>::get_obstacle()
{
	return obstacle;
}

template<class x>
inline void World<x>::add_obstacle(int ID, x *it)
{
	obstacle[ID] = it;
}


template<class x>
inline sf::Font *World<x>::get_font()
{
	return &this->font;
}


