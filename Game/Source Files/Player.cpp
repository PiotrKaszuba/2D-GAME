#include "Player.h"



Player::Player()
{
}

Player::Player(Unit base, World<Physical> *mapa, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down,
	sf::Keyboard::Key attack, sf::Keyboard::Key block, sf::Keyboard::Key kick, sf::Keyboard::Key use, sf::Keyboard::Key finish, sf::Keyboard::Key menu) : Unit(base)
{
	this->player_left = left;
	this->player_right = right;
	this->player_up = up;
	this->player_down = down;
	this->player_attack = attack;
	this->player_block = block;
	this->player_kick = kick;
	this->player_use = use;
	this->player_to_go = noway;
	this->player_finish = finish;
	this->player_menu = menu;
	this->player_in_menu = 0;
	this->player_finish_used = 0;
	this->player_score = 0;
    mapa->add_obstacle(this->ID, this);
	

}


Player::~Player()
{
}

sf::Keyboard::Key Player::get_player_left()
{
	return this->player_left;
}

sf::Keyboard::Key Player::get_player_right()
{
	return this->player_right;
}

sf::Keyboard::Key Player::get_player_up()
{
	return this->player_up;
}

sf::Keyboard::Key Player::get_player_down()
{
	return this->player_down;
}

sf::Keyboard::Key Player::get_player_block()
{
	return this->player_block;
}

sf::Keyboard::Key Player::get_player_attack()
{
	return this->player_attack;
}

sf::Keyboard::Key Player::get_player_kick()
{
	return this->player_kick;
}

sf::Keyboard::Key Player::get_player_use()
{
	return this->player_use;
}

sf::Keyboard::Key Player::get_player_finish()
{
	return this->player_finish;
}

sf::Keyboard::Key Player::get_player_menu()
{
	return this->player_menu;
}

bool Player::get_player_in_menu()
{
	return this->player_in_menu;
}

bool Player::get_player_finish_used()
{
	return this->player_finish_used;
}

int Player::get_player_score()
{
	return this->player_score;
}

void Player::set_player_score(int change)
{
	this->player_score += change;
}

way Player::get_player_to_go()
{
	return this->player_to_go;
}

void Player::set_player_to_go(way to_go)
{
	this->player_to_go = to_go;
}

void Player::check_event(sf::Event Event)
{
	if (sf::Joystick::isConnected(0))
	{
		if (Event.type == sf::Event::JoystickButtonPressed || Event.joystickMove.position == 100 || Event.joystickMove.position == -100)
			Event.type = sf::Event::KeyPressed;
		else if (Event.type == sf::Event::JoystickButtonReleased || abs(Event.joystickMove.position) < 0.8)
			Event.type = sf::Event::KeyReleased;


		switch (Event.joystickButton.button)
		{
		case 0:
			if (Event.joystickMove.position == 100 || abs(Event.joystickMove.position) < 0.8 )
				Event.key.code = this->get_player_right();
			else if(Event.joystickMove.position == -100)
				Event.key.code = this->get_player_left();
			else Event.key.code = this->get_player_use();
			break;
		case 1:
			if (Event.joystickMove.position == 100 || abs(Event.joystickMove.position) < 0.8)
				Event.key.code = this->get_player_down();
			else if (Event.joystickMove.position == -100)
				Event.key.code = this->get_player_up();
			else Event.key.code = this->get_player_kick();
			break;
		case 2:
			Event.key.code = this->get_player_block();
			break;
		case 3:
			Event.key.code = this->get_player_attack();
			break;
		case 8:
			Event.key.code = this->get_player_menu();
			break;
		case 9:
			Event.key.code = this->get_player_finish();
			break;
		}

		
		
	
	}
	
	if (Event.type == sf::Event::KeyReleased)
	{

		if (Event.key.code == this->get_player_up() || Event.key.code == this->get_player_down())
		{
			this->change_direction(y_none);


		}
		if (Event.key.code == this->get_player_left() || Event.key.code == this->get_player_right())
		{
			this->change_direction(x_none);

		}
		if (Event.key.code == this->get_player_block())
		{
			this->start_action(block, false);

		}
		if (Event.key.code == this->get_player_attack())
		{
			this->start_action(attack, false);

		}
		if (Event.key.code == this->get_player_use())
		{
			this->start_action(use, false);

		}
		if (Event.key.code == this->get_player_menu())
		{
			this->player_in_menu = 0;
		}

	}
	if (Event.type == sf::Event::KeyPressed)
	{


		if (Event.key.code == this->get_player_up())
		{
			this->change_direction(y_up);

		}

		if (Event.key.code == this->get_player_down())
		{
			this->change_direction(y_down);

		}

		if (Event.key.code == this->get_player_left())
		{
			this->change_direction(x_left);

		}

		if (Event.key.code == this->get_player_right())
		{
			this->change_direction(x_right);

		}
		if (Event.key.code == this->get_player_block())
		{
			this->start_action(block);
		}
		if (Event.key.code == this->get_player_attack())
		{
			this->start_action(attack);
		}
		if (Event.key.code == this->get_player_kick())
		{
			this->start_action(kick);
		}
		if (Event.key.code == this->get_player_use())
		{
			this->start_action(use);
		}
		if (Event.key.code == this->get_player_finish())
		{
			this->player_finish_used = 1;
		}
		if (Event.key.code == this->get_player_menu())
		{
			this->player_in_menu = 1;
		}
	}
}

void Player::update(World<Physical>*mapa)
{
	if (this->health > 0)
	{
		this->being_hit();
		this->Movement();
		this->attacking(mapa);
		this->useing();

		this->Border_Collision(mapa);
		this->Physical_Collision(mapa);
		this->Animate();

		this->regenerate();

		mapa->draw(*this);
		this->health_display_update(mapa);
	}
	else 
	{
		this->alive = false;
		this->player_finish_used = 1;
		mapa->get_obstacle()[this->ID]->zero_collision();
	}
}