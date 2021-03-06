#include "Object.h"



Object::Object()
{

}

Object::Object(int ID, int width, int height)
{
	this->ID = ID;
	this->width = width;
	this->height = height;
	
}

int Object::Get_ID()
{
	return this->ID;
}

int Object::Get_width()
{
	return this->width;
}

int Object::Get_height()
{
	return this->height;
}

void Object::Set_width(int width)
{
	this->width = width;
}

void Object::Set_height(int height)
{
	this->height = height;
}

void Object::zero_collision()
{
	this->width = 0;
	this->height = 0;
}


double solve_square_equation(double a, double b, double c, int type_of_result)
{
	double p = (-b) / (2 * a);
	if (type_of_result == 0) return p;
	double dx = pow(b, 2) - 4 * a * c;
	if (type_of_result == 1) return (p - sqrt(dx) / (2 * a));
	if (type_of_result == 2) return (p + sqrt(dx) / (2 * a));
	return 0;

}

Object::~Object()
{
}
