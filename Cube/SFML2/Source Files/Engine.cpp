#include "Engine.h"



Engine::Engine()
{
}

Engine::Engine(Game * game, World<Physical>* mapa)
{
	this->game = game;
	this->mapa = mapa;
}

void Engine::run()
{

	// introduce the game
	game->intro(this->mapa);


	//creating a collection of players and adding all players to it
	//makes it easier to check events
	std::vector<Object*> players;
	players.push_back(&*mapa->get_obstacle()[0]);
	//
	// used to order updating objects
	//bool alfa = 0;
	//
	// creating window 


	//putting game window in the top left hand corner
	mapa->setPosition(sf::Vector2i(0, 0));

	//game speed in frames per second
	mapa->setFramerateLimit(20);
	//
	while (mapa->isOpen())
	{

		// your event loop to trigger actions
		sf::Event event;
		while (mapa->pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				mapa->close();
			}
			// player event checking
			for each (Player* v in players)
			{
				//pass your event pool into the checks
				v->check_event(event);
			}





		}

		//remove stuff from window before drawing new frame
		mapa->clear();

		// collision check part 1. kick , 2. attack, 3. other guy collision, 4. kickin & attaking guy collision
		// 5. other guy center, 6. attaking guy center
		/*
		sf::RectangleShape vc(sf::Vector2f(36/4+70/5, 36/4+76/8));
		//vc.setOrigin(18,18);
		vc.setPosition(y.getPosition().x + 36 / 4 , y.getPosition().y - 18 - 76 / 8);
		mapa->draw(vc);

		sf::RectangleShape qc(sf::Vector2f( 54 / 5, 76 / 6));
		//qc.setOrigin(18, 18);
		qc.setPosition(y.getPosition().x + 36 / 2, y.getPosition().y );
		mapa->draw(qc);


		sf::RectangleShape gc(sf::Vector2f(36, 36));
		gc.setOrigin(18, 18);
		gc.setPosition(sf::Vector2f(x.getPosition().x, x.getPosition().y));
		mapa->draw(gc);

		sf::RectangleShape bc(sf::Vector2f(36, 36));
		bc.setOrigin(18, 18);
		bc.setPosition(sf::Vector2f(y.getPosition().x,y.getPosition().y));
		mapa->draw(bc);
		sf::CircleShape af(6, 30);
		af.setFillColor(sf::Color(100, 40, 150, 255));
		af.setPosition(x.getPosition());
		mapa->draw(af);
		//
		sf::CircleShape v(2, 10);
		v.setPosition(y.getPosition().x, y.getPosition().y);
		v.setOutlineColor(sf::Color::Cyan);
		v.setFillColor(sf::Color::Cyan);
		mapa->draw(v);
		*/


		// draw background
		/*
		for (int i = 0; i < mapa->getSize().y; i += 256)
		{
		for (int j = 0; j < mapa->getSize().x;j += 256)
		{
		backgroundv.setPosition(sf::Vector2f(j, i));
		backgroundv.update(mapa);
		}
		}

		exitbordertop.update(mapa);
		exitborderbot.update(mapa);
		exitborderleft.update(mapa);
		exitborderright.update(mapa);
		exitmiddlev.update(mapa);
		ladder_obj.setPosition(sf::Vector2f(mapa->getSize().x*(0.5 - 0.05) -  (ladder_obj.Get_width() + ladder_obj.get_sprite_sheet_animation(ladder_obj.get_animated_state() ).Get_type_of_animation_size_modifier().x )/ 2 - exitmiddlev.Get_width()/2, mapa->getSize().y / 2 - (ladder_obj.Get_height() + ladder_obj.get_sprite_sheet_animation(ladder_obj.get_animated_state()).Get_type_of_animation_size_modifier().y ) /2 ));
		mapa->draw(ladder_obj);
		ladder_obj.setPosition(sf::Vector2f(mapa->getSize().x*(0.5 - 0.05) - (ladder_obj.Get_width() + ladder_obj.get_sprite_sheet_animation(ladder_obj.get_animated_state()).Get_type_of_animation_size_modifier().x) / 2 - exitmiddlev.Get_width()/ 2, mapa->getSize().y / 2));
		ladder_obj.update(mapa);

		column_obj.update(mapa);
		// update other objects
		d.update(mapa);
		// update moving and higher level objects
		// alfa used to switch between the update order : default and from behind to balance priority
		if (alfa) {

		x.update(mapa);
		y.update(mapa);

		alfa = false;
		}
		else
		{
		y.update(mapa);
		x.update(mapa);

		alfa = true;
		} */
		//

		// update cube
		game->update(mapa);
		
			
		// showing all stuff
		mapa->display();
	}

}


Engine::~Engine()
{
}
