#include "Moving.h"



Moving::Moving()
{
}

Moving::Moving(Physical base) : Physical(base)
{

}

Moving::Moving(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical> *mapa, float speed, direction_x x, direction_y y) : Physical(ID,base, position,mapa)
{
	this->moving_speed = speed;
	this->change_direction(x);
    this->change_direction(y);
	mapa->add_obstacle(this->ID, this);
}

void Moving::Move(int x, int y)
{
		if (x>0)
			this->animated_side = r;
		if (x<0)
			this->animated_side = l;

	
		this->setPosition(this->getPosition().x+x*this->moving_speed, this->getPosition().y+y*this->moving_speed);
		this->set_use_item(NULL);
}



void Moving::Movement()
{
	if (this->animated_state == go)
	{
		if (this->moving_direction_y == y_up)
		{
			this->Move(0, -1);
		}

		if (this->moving_direction_y == y_down)
		{
			this->Move(0, 1);
		}

		if (this->moving_direction_x == x_left)
		{
			this->Move(-1, 0);
		}
		if (this->moving_direction_x == x_right)
		{
			this->Move(1, 0);
		}
	}
}

void Moving::Border_Collision(World<Physical>*mapa)
{
	if (this->getPosition().x - this->width/2 < 0 + mapa->Get_border_size().x/2)
	{
		this->Direct_Move(-(this->getPosition().x -this->width/2 - (mapa->Get_border_size().x / 2)), 0);
	}

	if (this->getPosition().x + this->width/2 > mapa->Get_width() + mapa->Get_border_size().x / 2)
	{
		this->Direct_Move(-(this->getPosition().x +this->width/2 - (mapa->Get_width()+mapa->Get_border_size().x/2)), 0);

	}

	if (this->getPosition().y - this->height/2 < 0 + mapa->Get_border_size().y/2)
	{
		this->Direct_Move(0, -(this->getPosition().y -this->height/2 - (mapa->Get_border_size().y / 2)));

	}
	if (this->getPosition().y + this->height/2 > mapa->Get_height() + mapa->Get_border_size().y/2)
	{
		this->Direct_Move(0,-(this->getPosition().y +this->height/2 - ( mapa->Get_height() + mapa->Get_border_size().y/2)));

	}
}



void Moving::change_side(side kierunek)
{
	this->animated_side = kierunek;
}

void Moving::change_direction(direction_x direction)
{
	if (this->animated_state < 5 && direction != x_none)
	{
		this->animated_state = go;
	}
	if (this->animated_state == go && direction == x_none && this->moving_direction_y == y_none)
		this->stop();
	this->moving_direction_x = direction;
	
}

void Moving::change_direction(direction_y direction)
{
	if (this->animated_state < 5 && direction != y_none)
	{
		this->animated_state = go;
	}
	if (this->animated_state==go && direction == y_none && this->moving_direction_x == x_none)
		this->stop();
	this->moving_direction_y = direction;
}

void Moving::stop()
{
	if (this->animated_state < 5)
	{
		if (this->animated_state == still)
		{
			this->animated_frame = 0;
		}
		this->animated_state = still;
	}
}


void Moving::update(World<Physical>*mapa)
{
	this->Movement();
	this->Border_Collision(mapa);
	this->Physical_Collision(mapa);
	this->Animate();
	mapa->draw(*this);

}

float Moving::get_moving_speed()
{
	return this->moving_speed;
}

void Moving::set_moving_speed(float speed)
{
	this->moving_speed = speed;
}


Moving::~Moving()
{
}
