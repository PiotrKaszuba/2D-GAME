#pragma once
#include "Object.h"



// a data type for animation based objects
// it's in Visible class because it is passed deeper than to sprite sheet - finished here
struct Sprite_Sheet_Data
{
	sf::Sprite data;
	int size;
	int width;
	int height;
	Type_of_Animation still;
	Type_of_Animation go;
	Type_of_Animation attack;
	Type_of_Animation interrupted;
	Type_of_Animation hit;
	Type_of_Animation block;
	Type_of_Animation kick;
	Type_of_Animation use;
};

// represents objects possible to draw that fit the system (it is sprite that is drawable)
class Visible :
	public Object, public sf::Sprite
{
public:
	Visible();
	// constructor which takes unit ID, Sprite Sheet Data and position
	Visible(int ID, Sprite_Sheet_Data base, sf::Vector2f position);
	~Visible();
	// updates should be called with a World argument object belongs to
	virtual void update(World<Physical> *mapa);
	//this method return the objects collision - a rectangle made of it's position, width, height
	sf::Rect<int> Get_Rect();
	float getXpos();
	float getYpos();
};

