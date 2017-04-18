#pragma once
#include "Room.h"

// It is an object that user controls
// stores key settings for actions
// create separate unit first, then using it, create player
class Player :
	public Unit
{
private:
	sf::Keyboard::Key player_left;
	sf::Keyboard::Key player_right;
	sf::Keyboard::Key player_up;
	sf::Keyboard::Key player_down;
	sf::Keyboard::Key player_attack;
	sf::Keyboard::Key player_block;
	sf::Keyboard::Key player_kick;
	sf::Keyboard::Key player_use;
	sf::Keyboard::Key player_finish;
	sf::Keyboard::Key player_menu;
	way player_to_go;
	bool player_in_menu;
	bool player_finish_used;
	int player_score;
public:
	Player();
	Player(Unit base, World<Physical> *mapa, sf::Keyboard::Key left = sf::Keyboard::A, sf::Keyboard::Key right = sf::Keyboard::D, sf::Keyboard::Key up = sf::Keyboard::W, sf::Keyboard::Key down = sf::Keyboard::S, sf::Keyboard::Key attack = sf::Keyboard::LControl,
		sf::Keyboard::Key block = sf::Keyboard::LAlt, sf::Keyboard::Key kick = sf::Keyboard::Space, sf::Keyboard::Key use = sf::Keyboard::E, sf::Keyboard::Key finish = sf::Keyboard::Escape, sf::Keyboard::Key menu = sf::Keyboard::Tab);
	~Player();
	sf::Keyboard::Key get_player_left();
	sf::Keyboard::Key get_player_right();
	sf::Keyboard::Key get_player_up();
	sf::Keyboard::Key get_player_down();
	sf::Keyboard::Key get_player_block();
	sf::Keyboard::Key get_player_attack();
	sf::Keyboard::Key get_player_kick();
	sf::Keyboard::Key get_player_use();
	sf::Keyboard::Key get_player_finish();
	sf::Keyboard::Key get_player_menu();
	virtual bool get_player_in_menu();
	virtual bool get_player_finish_used();
	virtual int get_player_score();
	virtual void set_player_score(int change);
	virtual way get_player_to_go();
	virtual void set_player_to_go(way to_go);

	// run this in 'player event checking' block in main or engine
	void check_event(sf::Event Event);

	virtual void update(World<Physical>*mapa);
};

