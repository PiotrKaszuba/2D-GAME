#pragma once
#include "Type_of_Animation.h"

class Physical;

// Basic object for all other
// It's purpose is to represent rectangle based objects
// This class is abstract, there is no way to draw it, because it does not store position
class Object
{
protected: 
	int ID;
	int width;
	int height;
public:
	Object();
	Object(int ID, int width, int height);
	int Get_ID();
	int Get_width();
	int Get_height();
	void Set_width(int width);
	void Set_height(int height);
	virtual void zero_collision();
	virtual void update(World<Physical> *mapa) = 0;
	// type_of_result returns:
	// 0 : p
	// 1 : x1 = (p - sqrt(dx)/2a)
	// 2 : x2 = (p + sqrt(dx)/2a)
	friend double solve_square_equation(double a, double b, double c, int type_of_result);
	~Object();
};

