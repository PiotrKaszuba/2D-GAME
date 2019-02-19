#include "Room.h"



void Room::hint_matching(World<Physical>* mapa, Cube<Room>* cube)
{
	int value = this->coordinates.x * 100 + this->coordinates.y * 10 + this->coordinates.z;
	int value2 = 0;
	if (this->coordinates.x != this->coordinates.y && this->coordinates.y != this->coordinates.z && this->coordinates.z != this->coordinates.x)
	{
		if (this->coordinates.x < this->coordinates.y  && this->coordinates.y < this->coordinates.z)
			value2 = 1;
		if (this->coordinates.x < this->coordinates.z && this->coordinates.z < this->coordinates.y)
			value2 = 2;
		if (this->coordinates.y < this->coordinates.x && this->coordinates.x < this->coordinates.z)
			value2 = 3;
		if (this->coordinates.z < this->coordinates.x && this->coordinates.x < this->coordinates.y)
			value2 = 4;
		if (this->coordinates.y < this->coordinates.z && this->coordinates.z < this->coordinates.x)
			value2 = 5;
		if (this->coordinates.z < this->coordinates.y && this->coordinates.y < this->coordinates.x)
			value2 = 6;
	}
	else if (this->coordinates.x == this->coordinates.y && this->coordinates.x == this->coordinates.z)
	{
		value2 = 1;
	}
	else
	{
		if (this->coordinates.x < this->coordinates.z)
			value2 = 1;
		if (this->coordinates.x == this->coordinates.z)
			value2 = 2;
		if (this->coordinates.x > this->coordinates.z)
			value2 = 3;
	}
	if
		(cube->get_sum() == this->coordinates.x + this->coordinates.y + this->coordinates.z &&
			value%cube->get_divisibility() == 0 &&
			cube->get_does_not_contain() != this->coordinates.x && cube->get_does_not_contain() != this->coordinates.y && cube->get_does_not_contain() != this->coordinates.z &&
			cube->get_permutation() == value2
			)
		this->final_room = true;
	else
		this->final_room = false;


	bool compatible = 0;
	int counter = 0;
	while (!compatible)
	{
		if (counter > 3000)
		{
			counter = 0;
			this->hint_type = dependance(rand() % 5);
		}
		counter += 1;
		hint = sf::Vector3<char>(rand() % 10, rand() % 10, rand() % 10);
		if (cube->get_rooms()[hint.x][hint.y][hint.z].get_hint_truth_loaded())
		{
			switch (this->hint_type)
			{
			case sum_higher:
				if ((cube->get_rooms()[hint.x][hint.y][hint.z].get_hint_truth() == bool(cube->get_sum() > this->hint.x + this->hint.y + this->hint.z)))
					compatible = 1;
				break;
			case sum_lower:
				if ((cube->get_rooms()[hint.x][hint.y][hint.z].get_hint_truth() == bool(cube->get_sum() < this->hint.x + this->hint.y + this->hint.z)))
					compatible = 1;
				break;
			case divisibility:
				value = this->hint.x * 100 + this->hint.y * 10 + this->hint.z;
				if ((cube->get_rooms()[hint.x][hint.y][hint.z].get_hint_truth() == bool(value%cube->get_divisibility() == 0)))
					compatible = 1;
				break;
			case does_not_contain:
				if ((cube->get_rooms()[hint.x][hint.y][hint.z].get_hint_truth() == bool(cube->get_does_not_contain() != this->hint.x && cube->get_does_not_contain() != this->hint.y && cube->get_does_not_contain() != this->hint.z)))
					compatible = 1;
				break;
			case permutation:
				value = 0;
				if (this->hint.x != this->hint.y && this->hint.y != this->hint.z && this->hint.z != this->hint.x)
				{
					if (this->hint.x < this->hint.y && this->hint.y < this->hint.z)
						value = 1;
					if (this->hint.x < this->hint.z && this->hint.z < this->hint.y)
						value = 2;
					if (this->hint.y < this->hint.x && this->hint.x < this->hint.z)
						value = 3;
					if (this->hint.z < this->hint.x && this->hint.x < this->hint.y)
						value = 4;
					if (this->hint.y < this->hint.z && this->hint.z < this->hint.x)
						value = 5;
					if (this->hint.z < this->hint.y && this->hint.y < this->hint.x)
						value = 6;
				}
				else if (this->hint.x == this->hint.y && this->hint.x == this->hint.z)
				{
					value = 1;
				}
				else
				{
					if (this->hint.x < this->hint.z)
						value = 1;
					if (this->hint.x == this->hint.z)
						value = 2;
					if (this->hint.x > this->hint.z)
						value = 3;
				}
				if ((cube->get_rooms()[hint.x][hint.y][hint.z].get_hint_truth() == bool(cube->get_permutation() == value)))
					compatible = 1;
				break;

			}
		}
		else
		{
			compatible = 1;
			cube->get_rooms()[this->hint.x][this->hint.y][this->hint.z].set_hint_truth_loaded(true);
			switch (this->hint_type)
			{
			case sum_higher:
				cube->get_rooms()[this->hint.x][this->hint.y][this->hint.z].set_hint_truth(bool(cube->get_sum() > this->hint.x + this->hint.y + this->hint.z));
				break;
			case sum_lower:
				cube->get_rooms()[this->hint.x][this->hint.y][this->hint.z].set_hint_truth(bool(cube->get_sum() < this->hint.x + this->hint.y + this->hint.z));
				break;
			case divisibility:
				value = this->hint.x * 100 + this->hint.y * 10 + this->hint.z;
				cube->get_rooms()[this->hint.x][this->hint.y][this->hint.z].set_hint_truth(bool(value%cube->get_divisibility() == 0));
				break;
			case does_not_contain:
				cube->get_rooms()[this->hint.x][this->hint.y][this->hint.z].set_hint_truth(bool(cube->get_does_not_contain() != this->hint.x && cube->get_does_not_contain() != this->hint.y && cube->get_does_not_contain() != this->hint.z));
				break;
			case permutation:
				value = 0;
				if (this->hint.x != this->hint.y && this->hint.y != this->hint.z && this->hint.z != this->hint.x)
				{
					if (this->hint.x < this->hint.y && this->hint.y < this->hint.z)
						value = 1;
					if (this->hint.x < this->hint.z && this->hint.z < this->hint.y)
						value = 2;
					if (this->hint.y < this->hint.x && this->hint.x < this->hint.z)
						value = 3;
					if (this->hint.z < this->hint.x && this->hint.x < this->hint.y)
						value = 4;
					if (this->hint.y < this->hint.z && this->hint.z < this->hint.x)
						value = 5;
					if (this->hint.z < this->hint.y && this->hint.y < this->hint.x)
						value = 6;
				}
				else if (this->hint.x == this->hint.y && this->hint.x == this->hint.z)
				{
					value = 1;
				}
				else
				{
					if (this->hint.x < this->hint.z)
						value = 1;
					if (this->hint.x == this->hint.z)
						value = 2;
					if (this->hint.x > this->hint.z)
						value = 3;
				}
				cube->get_rooms()[this->hint.x][this->hint.y][this->hint.z].set_hint_truth(bool(cube->get_permutation() == value));
				break;

			}

		}

	}
}

Room::Room()
{
}


Room::~Room()
{
}

Room::Room(sf::Vector3<char> coordinates)
{
	this->coordinates = coordinates;
	this->feature = NULL;
	this->final_room = 0;
	this->background = NULL;
	this->hint_truth_loaded = 0;
	this->room_initialized = 0;
	hint_type = dependance(rand() % 5);
	this->floor_type = (coordinates.x + coordinates.y + coordinates.z) % 3;
	this->alpha = 0;
	this->feature_alive = 0;
}

sf::Vector3<char> Room::get_coordinates()
{
	return this->coordinates;
}

sf::Vector3<char> Room::get_hint()
{
	return this->hint;
}

dependance Room::get_hint_type()
{
	return this->hint_type;
}

bool Room::get_hint_truth()
{
	return this->hint_truth;
}

void Room::set_hint_truth(bool hint_truth)
{
	this->hint_truth = hint_truth;
}

bool Room::get_hint_truth_loaded()
{
	return this->hint_truth_loaded;
}

void Room::set_hint_truth_loaded(bool hint_truth_loaded)
{
	this->hint_truth_loaded = hint_truth_loaded;
}

bool Room::get_room_initialized()
{
	return this->room_initialized;
}

bool Room::get_final_room()
{
	return this->final_room;
}

Visible * Room::get_background()
{
	return this->background;
}

Room_Feature * Room::get_feature()
{
	return this->feature;
}

char Room::get_feature_value()
{
	return this->feature_value;
}

bool Room::get_feature_alive()
{
	return this->feature_alive;
}

void Room::drop_bonus(World<Physical>* mapa, Sprite_Sheet_Data ** graphics, float multiplier)
{
	this->feature_value = 10;
	switch ((this->coordinates.x + this->coordinates.y + this->coordinates.y) % 3)
	{
	case 0:
		this->feature_data.integer_value = 2;
		this->feature_data.real_value = 4*multiplier;
		this->feature_data.graphic = graphics[12];
		break;
	case 1:
		this->feature_data.integer_value = 1;
		this->feature_data.real_value = 0.0020 * multiplier;
		this->feature_data.graphic = graphics[13];
		break;
	case 2:
		this->feature_data.integer_value = 3;
		this->feature_data.real_value = 1.6 * multiplier;
		this->feature_data.graphic = graphics[14];
		break;
	}
	

	this->feature_data.position = sf::Vector2f(this->feature->getXpos(), this->feature->getYpos());
	delete mapa->get_obstacle()[this->feature->Get_ID()];
	mapa->Set_objects(-1);
	this->feature = new Bonus_Holder(8, *this->feature_data.graphic, mapa, this->feature_data.position, (bonus_type)this->feature_data.integer_value, this->feature_data.real_value);
}

char Room::get_floor_type()
{
	return this->floor_type;
}

void Room::exit_room(World<Physical> *mapa)
{
	delete this->background;
	
	for (int i = 1; i < mapa->Get_objects();i++)
	{
		delete mapa->get_obstacle()[i];
	}
	mapa->Set_objects(1 - mapa->Get_objects());
}

void Room::initialize(World<Physical> *mapa, Cube<Room> *cube, Sprite_Sheet_Data **graphics, float multiplier)
{

	if (!this->room_initialized)
	{
		this->hint_matching(mapa, cube);
		

		if (!this->get_hint_truth_loaded())
		{
			this->hint_truth = rand() % 2;
			this->hint_truth_loaded = true;
		}

		if (this->coordinates.x % 9 == 0 && this->coordinates.y % 9 == 0 && this->coordinates.z % 9 == 0) {
			this->feature_value = 10;
			this->feature_data.integer_value = 0;
			this->feature_data.real_value = 50;
			this->feature_data.graphic = graphics[11];
			this->feature_data.position = sf::Vector2f(float(rand() % (mapa->getSize().x-mapa->Get_border_size().x) + mapa->Get_border_size().x / 2), float(rand() % (mapa->getSize().y - mapa->Get_border_size().y) + mapa->Get_border_size().y / 2));

		}
		else
			this->feature_value = rand() % 10;
		switch (this->feature_value)
		{
		case 5:
			this->feature_data.real_value = 100*multiplier;
			break;
		}
		this->feature_alive = true;
		this->room_initialized = true;
	}


	background = new Visible(-1, *graphics[2 + this->floor_type], sf::Vector2f(0, 0));
	Exit *exitbordertop = new Exit(1, *graphics[5], sf::Vector2f(mapa->getSize().x / 2, graphics[5]->height / 2), mapa, north);
	Exit *exitborderbot = new Exit(2, *graphics[5], sf::Vector2f(mapa->getSize().x / 2, mapa->getSize().y - graphics[5]->height / 2), mapa, south);
	Exit *exitborderleft = new Exit(3, *graphics[5], sf::Vector2f(graphics[5]->width / 2, mapa->getSize().y / 2), mapa, east);
	Exit *exitborderright = new Exit(4, *graphics[5], sf::Vector2f(mapa->getSize().x - graphics[5]->width / 2, mapa->getSize().y / 2), mapa, west);
	Exit *exitmiddlev = new Exit(5, *graphics[6], sf::Vector2f(mapa->getSize().x / 2, mapa->getSize().y / 2), mapa, downstairs);
	
	Exit *ladder_obj= new Exit(6, *graphics[7], sf::Vector2f(0, 0), mapa, upstairs, 3);
	ladder_obj->setPosition(sf::Vector2f(mapa->getSize().x*(0.5 - 0.05) - (ladder_obj->Get_width() + ladder_obj->get_sprite_sheet_animation(ladder_obj->get_animated_state()).Get_type_of_animation_size_modifier().x) / 2 - exitmiddlev->Get_width() / 2, mapa->getSize().y / 2));

	Column *column_obj = new Column(7, *graphics[8], sf::Vector2f(0, 0), mapa, this->hint_truth, this->hint,this->hint_type);
	column_obj->setPosition(sf::Vector2f(mapa->getSize().x*(0.5 + 0.05) + (column_obj->Get_width() + column_obj->get_sprite_sheet_animation(column_obj->get_animated_state()).Get_type_of_animation_size_modifier().y * column_obj->getScale().x) / 2 + exitmiddlev->Get_width() / 2, mapa->getSize().y / 2 - column_obj->Get_height() + exitmiddlev->Get_height() / 2));
	
	
	if (this->feature_alive)
	{
		switch (this->feature_value)
		{
		case 3:
			this->feature = new Damage_Trap_Spreader(8, 30, *graphics[9], mapa, 160, 1.75*multiplier);
			break;
		case 4:
			this->feature = new Projectile_Shooter(8, 15, *graphics[10], mapa, 22.0, 6*multiplier);
			break;
		case 5:
			this->feature = new Enemy(8, *graphics[1], mapa, mapa->get_obstacle()[rand() % 6 + 1]->getPosition(), this->feature_data.real_value, 10*multiplier);
			break;
		case 10:
			this->feature = new Bonus_Holder(8, *this->feature_data.graphic, mapa, this->feature_data.position, (bonus_type)this->feature_data.integer_value, this->feature_data.real_value);
			break;
		}
	}
	else {
		this->feature = NULL;
	}
	

}

void Room::update(World<Physical>* mapa)
{
	for (int i = 0; i < mapa->getSize().y; i += this->background->Get_height())
	{
		for (int j = 0; j < mapa->getSize().x; j += this->background->Get_width())
		{

			this->background->setPosition(sf::Vector2f(j + this->background->Get_width() / 2, i + this->background->Get_height() / 2));
			this->background->update(mapa);
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		mapa->get_obstacle()[i]->update(mapa);
	}
	if (this->feature_alive)
	{
		if ((3 <= this->feature_value && this->feature_value <= 4) || this->feature_value == 10)
		{
			if (this->feature)
				this->feature->update(mapa);
		}
	}
		if (alpha) {

			mapa->get_obstacle()[0]->update(mapa);
			if (this->feature_value == 5)
				if (this->feature)
					if (this->feature_alive)
				{
					this->feature->update(mapa);
					this->feature_data.real_value = this->feature->get_health();
				}

			alpha = false;
		}
		else
		{
			if (this->feature_value == 5)
				if (this->feature)
					if (this->feature_alive)
				       {
					this->feature->update(mapa);
					this->feature_data.real_value = this->feature->get_health();
				       }
			mapa->get_obstacle()[0]->update(mapa);

			alpha = true;
		}
	
	if (this->feature)
	this->feature_alive = this->feature->get_alive();
}
