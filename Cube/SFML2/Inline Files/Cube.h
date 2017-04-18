#pragma once
#include "Game.h"


// this class represents the whole game arena as it stores all rooms and dependencies between them
// this is the only object to be updated as it updates active room which updates all objects in it
// index 0 in the World object is set to be a player
// Rooms save other objects in :
// 1-4 border exits
// 5 middle exit
// 6 ladder exit
// 7 column
// 8+ room feature objects ( depend on room feature )
template <class x>
class Cube : public Game
{
private:
	//start time
	int start_time;
	//time to finish the game
	int time;
	//3D array to store all rooms
	x *** rooms;
	//one of numbers describing this game's cube
	char sum;
	//one of numbers describing this game's cube
	char divisibility;
	//one of numbers describing this game's cube
	char permutation;
	//one of numbers describing this game's cube
	char does_not_contain;
	//coordinates of room player is in
	sf::Vector3<char> active_room;
	//set of all graphics for game
	Sprite_Sheet_Data ** graphics;
	//object to show time left
	sf::Text timer;
	//finish text dependant on language
	std::string finish[2];
	//chosen language, 0 Polish, 1 English
	char language;
public:

	//Values to call with
	// sum 0-27 (might be limited to something like 3-24 but it disables a few rooms to be final)
	// divisibility 2-11 (suggested -> might be higher) discluding 10 (system removes 10 automatically)
	// permutation 1-6 (should not change)
	// does_not_contain 0-9
	//constructor also contains game set of graphics, World and time to finish the game
	Cube(char sum, char divisibility, char permutation, char does_not_contain, Sprite_Sheet_Data **graphics, World<Physical> *mapa, int time = 144000);
	sf::Vector3<char> get_active_room();
	void set_active_room(sf::Vector3<char> active_room);
	x *** get_rooms();
	char get_sum();
	char get_divisibility();
	char get_permutation();
	char get_does_not_contain();
	//highest level update, manages game states (like game finish) and room leaving
	void update(World<Physical> *mapa);
	//manages room leaving
	void check_and_leave_room(World<Physical> *mapa);
	//checks how many final rooms are in the whole cube
	int number_of_final_rooms();
	//update for timer called in this main update
	void timer_update(World<Physical> *mapa);
	//when time is finished (when you die time finished) this is called, calculates and shows player his result
	void end(bool victory, World<Physical> *mapa);
	//a function showing screen of language choice and returning decision made
	char language_choice(World<Physical> *mapa);
	//shows an info screen with given text that is skipped with any keyboard click
	void info_screen(World<Physical> *mapa, std::string text, std::string moveon);
	//shows info screens with game plot and rules before game starts and lets player choose language
	void intro(World<Physical> *mapa);
	//returns modified time/timeleft value to multiply values
	//doubles everytime time halves
	float multiplier()
	{
		return  1.0 + log2f((float)start_time / time);
	}
	
	//
	void moja_funkcja(World<Physical> *mapa);

	Cube()
	{
	}

	~Cube()
	{
		
		for (int x = 0;x < 10;x++)
		{
			
			for (int y = 0; y < 10;y++)
			{
				delete[] this->rooms[x][y];
			}
			delete[] this->rooms[x];
		}
		delete[] this->rooms;
	}
};

template<class x>
inline Cube<x>::Cube(char sum, char divisibility, char permutation, char does_not_contain, Sprite_Sheet_Data **graphics, World<Physical> *mapa, int time)
{
	this->language = 0;
	this->finish[0] = "";
	this->finish[1] = "";
	this->timer.setFont(*mapa->get_font());
	this->timer.setColor(sf::Color::Yellow);
	this->time = time;
	this->start_time = time;
	this->sum = sum;
	this->divisibility = divisibility;
	this->permutation = permutation;
	this->does_not_contain = does_not_contain;
	if (this->divisibility % 3 == 0 && this->sum % 3 != 0)
	{
		this->sum /= 3;
		this->sum *= 3;
		this->sum += 3 * (sum % 3 - 1);
	}
	while (this->divisibility == 10)
	{
		this->divisibility = rand() % 10 + 2;
	}
	this->rooms = new Room**[10];
	for (int x = 0;x < 10;x++)
	{
		this->rooms[x] = new Room*[10];
		for (int y = 0; y < 10;y++)
		{
			this->rooms[x][y] = new Room[10];
			for (int z = 0;z < 10;z++)
			{
				this->rooms[x][y][z] = Room(sf::Vector3<char>(x, y, z));
			}
		}
	}
	this->graphics = graphics;
	this->active_room = sf::Vector3<char>(rand() % 10, rand() % 10, rand() % 10);
	this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].initialize(mapa, this, this->graphics, this->multiplier());

	
	



	int finals = 0;
	while (!finals)
	{
		finals = this->number_of_final_rooms();
		if (!finals)
		{
			int a = rand() % 4;
			if (a == 0)
				this->sum = rand() % 28;
			if (a == 1)
				this->divisibility = rand() % 10 + 2;
			if (a == 2)
				this->permutation = rand() % 6 + 1;
			if (a == 3)
				this->does_not_contain = rand() % 10;
			if (this->divisibility % 3 == 0 && this->sum % 3 != 0)
			{
				this->sum /= 3;
				this->sum *= 3;
				this->sum += 3 * (sum % 3 - 1);
			}
			while (this->divisibility == 10)
			{
				this->divisibility = rand() % 10 + 2;
			}
		}
	}






}

template<class x>
inline sf::Vector3<char> Cube<x>::get_active_room()
{
	return this->active_room;
}

template<class x>
inline void Cube<x>::set_active_room(sf::Vector3<char> active_room)
{
	this->active_room = active_room;
}

template<class x>
inline x *** Cube<x>::get_rooms()
{
	return this->rooms;
}

template<class x>
inline char Cube<x>::get_sum()
{
	return this->sum;
}

template<class x>
inline char Cube<x>::get_divisibility()
{
	return this->divisibility;
}

template<class x>
inline char Cube<x>::get_permutation()
{
	return this->permutation;
}

template<class x>
inline char Cube<x>::get_does_not_contain()
{
	return this->does_not_contain;
}

template<class x>
inline void Cube<x>::check_and_leave_room(World<Physical>* mapa)
{
	if (mapa->get_obstacle()[0]->get_player_to_go() != noway)
	{
		bool going = 1;
		if (mapa->get_obstacle()[0]->get_player_to_go() == east)
		{
			if (this->active_room.x > 0)
			{
				this->active_room.x -= 1;
				mapa->get_obstacle()[0]->setPosition(mapa->get_obstacle()[4]->getPosition());
			}
			else going = 0;
		}

		if (mapa->get_obstacle()[0]->get_player_to_go() == south)
		{
			if (this->active_room.y > 0)
			{
				this->active_room.y -= 1;
				mapa->get_obstacle()[0]->setPosition(mapa->get_obstacle()[1]->getPosition());
			}
			else going = 0;
		}

		if (mapa->get_obstacle()[0]->get_player_to_go() == downstairs)
		{
			if (this->active_room.z > 0)
			{
				this->active_room.z -= 1;
				mapa->get_obstacle()[0]->setPosition(mapa->get_obstacle()[6]->getPosition());
			}
			else going = 0;
		}

		if (mapa->get_obstacle()[0]->get_player_to_go() == west)
		{
			if (this->active_room.x < 9)
			{
				this->active_room.x += 1;
				mapa->get_obstacle()[0]->setPosition(mapa->get_obstacle()[3]->getPosition());
			}
			else going = 0;
		}

		if (mapa->get_obstacle()[0]->get_player_to_go() == north)
		{
			if (this->active_room.y < 9)
			{
				this->active_room.y += 1;
				mapa->get_obstacle()[0]->setPosition(mapa->get_obstacle()[2]->getPosition());
			}
			else going = 0;
		}

		if (mapa->get_obstacle()[0]->get_player_to_go() == upstairs)
		{
			if (this->active_room.z < 9)
			{
				this->active_room.z += 1;
				mapa->get_obstacle()[0]->setPosition(mapa->get_obstacle()[5]->getPosition());
			}
			else going = 0;
		}

		if (going)
		{
			this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].exit_room(mapa);

			this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].initialize(mapa, this, graphics, this->multiplier());


			//std::cout << (int)this->active_room.x << (int)this->active_room.y << (int)this->active_room.z << std::endl;

		}
		mapa->get_obstacle()[0]->set_player_to_go(noway);
	}
}

template<class x>
inline void Cube<x>::update(World<Physical>* mapa)
{
	//if finished
	if (mapa->get_obstacle()[0]->get_player_finish_used())
	{
		if (mapa->get_obstacle()[0]->get_alive())
		{
			mapa->get_obstacle()[0]->set_player_score(this->time);
		}
		this->time = 0;
	}

	// if playing
	if (this->time > 0)
	{
		//if leaving room
		this->check_and_leave_room(mapa);
		//drop bonus when enemy dies, here because of need to pass graphics
		if (!this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].get_feature_alive() && this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].get_feature_value() == 5)
		{
			switch (rand() % 2)
			{
			case 0:
				break;
			case 1:
				this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].drop_bonus(mapa, this->graphics, this->multiplier());
			}
		}

		//update
		this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].update(mapa);
		
		//if menu
		if (mapa->get_obstacle()[0]->get_player_in_menu())
		{
			mapa->clear();
			this->timer_update(mapa);
		}



		this->time -= 1;
	}
	else
	{
		if (mapa->get_obstacle()[0]->get_alive() )
		{
			this->end(this->rooms[this->active_room.x][this->active_room.y][this->active_room.z].get_final_room(), mapa);
		}
		else 
			this->end(false, mapa);
	}
}

template<class x>
inline int Cube<x>::number_of_final_rooms()
{
	int finals = 0;
	for (int x = 0; x < 10;x++)
	{
		for (int y = 0; y < 10;y++)
		{
			for (int z = 0; z < 10;z++)
			{
				int value = x * 100 + y * 10 + z;
				int value2 = 0;
				if (x != y && y != z && z != x)
				{
					if (x < y  && y < z)
						value2 = 1;
					if (x < z && z < y)
						value2 = 2;
					if (y < x && x < z)
						value2 = 3;
					if (z < x && x < y)
						value2 = 4;
					if (y < z && z < x)
						value2 = 5;
					if (z < y && y < x)
						value2 = 6;
				}
				else if (x == y && x == z)
				{
					value2 = 1;
				}
				else
				{
					if (x < z)
						value2 = 1;
					if (x == z)
						value2 = 2;
					if (x > z)
						value2 = 3;
				}
				if
					(this->get_sum() == x + y + z &&
						value%this->get_divisibility() == 0 &&
						this->get_does_not_contain() != x && this->get_does_not_contain() != y && this->get_does_not_contain() != z &&
						this->get_permutation() == value2
						)
				{
					finals += 1;
				//std::cout << x << y << z << std::endl;
				}

			}
		}
	}
	//std::cout << finals;
	return finals;
	
}

template<class x>
inline void Cube<x>::timer_update(World<Physical> *mapa)
{
	int a = this->time / 20;
	int b = a / 3600;
	int c = (a - b * 3600) / 60;
	int d = (a - b * 3600 - c * 60);
	a = 36;
	if (b > 10) a += 10;
	if (c > 10) a += 10;
	if (d > 10) a += 10;
	this->timer.setString(std::to_string(b).append(std::string(":").append(std::to_string(c).append(std::string(":").append(std::to_string(d))))));
	this->timer.setPosition(mapa->getSize().x / 2 - a, mapa->getSize().y / 2 - 30.f);
	mapa->draw(this->timer);
}

template<class x>
inline void Cube<x>::end(bool victory, World<Physical> *mapa)
{
	if (victory)
	{
		std::string temp = this->finish[1];
		mapa->get_obstacle()[0]->set_player_score(mapa->get_obstacle()[0]->get_health() * 100);
		mapa->get_obstacle()[0]->deal_damage(mapa->get_obstacle()[0], mapa->get_obstacle()[0]->get_health());
		this->timer.setString(temp.append(std::to_string(mapa->get_obstacle()[0]->get_player_score())));
		this->timer.setPosition(mapa->getSize().x / 2 - 290 + this->language*60, mapa->getSize().y / 2 - 30.f);
		this->timer.setColor(sf::Color::Green);
	}
	else
	{
		this->timer.setString(this->finish[0]);
		this->timer.setPosition(mapa->getSize().x / 2 - 70 + 5*this->language, mapa->getSize().y / 2 - 30.f);
		this->timer.setColor(sf::Color::Red);
	}
	mapa->draw(this->timer);
}

template<class x>
inline void Cube<x>::intro(World<Physical> *mapa){
	mapa->setPosition(sf::Vector2i(0, 0));
	//this->moja_funkcja(mapa);
	char language = this->language_choice(mapa);
	std::string *info = new std::string[9];
	switch (language)
	{
	case 'p':
		this->finish[0] = "Porazka!";
		this->finish[1] = "Zwyciestwo! Punkty: ";
		info[0] = "Nacisnij dowolny przycisk";
		info[1] = "Jestes naukowcem prowadzacym eksperyment. Razem z grupa specjalistow konstruujesz wirtualny szescian, superpulapke. Czy dasz rade sie z niego wydostac?";
		info[2] = "Zostajesz umieszczony w jednym z tysiaca pokoi szescianu. Kazdy wymiar posiada 10 pokoi. Oznaczone sa one XYZ. Os X numeracji pokoi zwieksza swoje wartosci na wschod, os Y na polnoc, a os Z w gore, po drabinie.";
		info[3] = "Intensywnie myslac, przypominasz sobie, ze w pewnym momencie szescian ulega przesortowaniu, a w pokojach panuje proznia na czas tego procesu. Powietrze zostaje odessane w kilku kluczowych punktach. To jedyna szansa, aby sie wydostac.";
		info[4] = "Poruszasz sie przy pomocy klawiszy WSAD, walka piesciami - LCTRL, kopniak SPACE, blok LALT, uzycie/wejscie E, pozostaly czas/pomoc TAB, automatyczne odczekanie do konca czasu ESCAPE.";
		info[5] = "Aby zwyciezyc musisz po uplynieciu czasu znajdowac sie w jednym z Pokoi Wyjsciowych. W niektorych pokojach znajduja siê pulapki i agresywni wiezniowie, ktorzy rowniez tutaj trafili. W kazdym pokoju znajduje siê wskazowka dotyczaca Pokoi Wyjsciowych.";
		info[6] = "Szescian opisany jest za pomoca 4 liczb: Sumy, Dzielnika, Permutacji i Braku. Suma oznacza sume wspolrzednych Pokoi Wyjsciowych. W Pokoju Wyjsciowym XYZ liczba 100*X+10*Y+Z jest podzielna przez Dzielnik. Dzielnik przyjmuje wartosci od 2 do 9 lub 11. Wartosc Permutacji jest kolejnym numerem w posortowaniu rosnacym wszystkich mozliwych permutacji ciagu XYZ o wartosci 100*pierwszy+10*drugi+trzeci. Cyfra o wartosci rownej Braku nie wystepuje w Pokoju Wyjsciowym XYZ.";
		info[7] = "Kazda wskazowka sklada sie z 3 czesci: Znacznika, Wspolrzednych i Koloru. Znacznik informuje nas jakiej z liczb dotyczy wskazowka. Znaczniki '>' / '<' oznaczaja ze Suma jest wieksza/mniejsza od sumy wspolrzednych pokoju ktorego dotyczy wskazowka. Znaczniki '|' '!' '?' dotycza kolejno Dzielnika, Permutacji i Braku. Informuja o tym ze pokoj ktorego dotyczy wskazowka moglby byc, pod wzgledem tej liczby, Pokojem Wyjsciowym. Wspolrzedne dotycza pokoju do ktorego odnosi sie wskazowka. Kolor wskazowki w danym pokoju dotyczy wszystkich wskazowek, ktore do niego prowadzily i weryfikuje ich prawdziwosc: zielony - sa prawda, czerwony - sa falszem.";
		info[8] = "Masz 2 godziny. Ruszaj!";
		this->language = 0;
		break;
	case 'e' :
		this->finish[0] = "Defeat!";
		this->finish[1] = "Victory! Points: ";
		info[0] = "Press any key to continue";
		info[1] = "You are a scientist and do another project. With group of specialists you design a virtual cube, a great trap. Are you able to escape it?";
		info[2] = "You find yourself inside one out of thousand rooms. Each dimension has 10 rooms. They are signed with XYZ. X axis of room numeration increases to east, Y axis to north and Z axis - upstairs, up the ladder.";
		info[3] = "Thinking, you remember that there is a moment when cube is resorted and a vacuum is created in rooms for the process. Air gets sucked out in a few key points. This is the only chance to get out.";
		info[4] = "You can move by pressing keys WSAD, fight with arms - LCTRL, kick SPACE, block LALT, use/enter E, time left/help TAB, automatic wait to the end of time ESCAPE.";
		info[5] = "To win you have to be in one of Exit Rooms when time elapses. In some rooms there are traps and aggressive prisoners who also got here. In every room though there is a hint about Exit Rooms.";
		info[6] = "Cube is described by 4 numbers: Sum, Divider, Permutation and Lack. Sum means the sum of Exit Rooms coordinates. In Exit Room XYZ value 100*X+10*Y+Z is divisible by Divider. Divider gets values between 2 and 9 or 11. Value or Permutation is the successive number in ascending order of all of possible permutations of XYZ series with value 100*first+10*second+third. Digit of value equal to Lack does not occur in Exit Room.";
		info[7] = "Every hint is made up of 3 parts: Mark, Coordinates and Colour. Mark let us know which number the hint refers to. Marks '>' / '<' mean that Sum is higher/lower than sum of, the room the hint is referring to, coordinates. Marks '|' '!' '?' refer respectively to Divider, Permutation and Lack. They inform that room which the hint refers to might be, for this number, Exit Room. Coordinates relate to room the hint refers to. Colour of the hint in a given room applies to every hint which led to it and checks its authenticity: green - true, red - false.";
		info[8] = "You got 2 hours. Go!";
		this->language = 1;
	}

	for (int i = 1; i <= 8; i++)
	{
		this->info_screen(mapa, info[i], info[0]);
	}
	delete[] info;
	this->timer.setScale(1, 1);
}

template <class x>
inline char Cube<x>::language_choice(World<Physical> *mapa)
{
	this->timer.setScale(1, 1);
	this->timer.setString("Polski - nacisnij P\n English - press E");
	this->timer.setPosition(mapa->getSize().x / 2 - 10.5/2 * this->timer.getScale().x *this->timer.getString().getSize(), mapa->getSize().y/2 - 35.f * this->timer.getScale().y);
	mapa->draw(this->timer);

	mapa->display();

	
	while (true)
	{
		sf::Event even;
		while (mapa->pollEvent(even)) {
			if (even.type == sf::Event::KeyPressed)
			{

				if (even.key.code == sf::Keyboard::P)
				{
					return 'p';
				}

				if (even.key.code == sf::Keyboard::E)
				{
					return 'e';
				}
			}
		}
	}

}
	

template <class x>
inline void Cube<x>::info_screen(World<Physical> *mapa, std::string text, std::string moveon)
{
	this->timer.setScale(1, 1);
	this->timer.setString(moveon);
	this->timer.setPosition(mapa->getSize().x / 2 - 10.5 * this->timer.getScale().x *this->timer.getString().getSize(), mapa->getSize().y - 35.f * this->timer.getScale().y);
	mapa->draw(this->timer);
	float lines_with_full_size = 8;
	float number_of_signs = 25;
	int lines=0;
	int x = text.size();
	while (x > 0)
	{
		if (lines*this->timer.getScale().x < lines_with_full_size)
		{
			lines++;
			x -= number_of_signs/this->timer.getScale().x;
			if (lines > (int) lines_with_full_size)
			{
				this->timer.setScale(this->timer.getScale().x, this->timer.getScale().y-0.07);

			}
		}
		else
		{
			this->timer.setScale(this->timer.getScale().x - 0.1, this->timer.getScale().y);
			x -= lines*(number_of_signs/ this->timer.getScale().x - number_of_signs / (this->timer.getScale().x + 0.1));
		}

	}
	int whole_text = 0;
	for (int i = 0; i < lines;i++)
	{
		if (whole_text >= text.size()) break;
		
		int loop = number_of_signs / this->timer.getScale().x - 5.f + whole_text;
		if (loop < text.size())
		{
			while (text.at(loop) != ' ')
			{
				loop += 1;
				if (loop >= text.size()) break;
			}
		}
		else loop = text.size() - 1;

		this->timer.setString(text.substr(whole_text, loop+1-whole_text));
		this->timer.setPosition(mapa->getSize().x / 2 - 10.5 * this->timer.getScale().x *this->timer.getString().getSize(), (mapa->getSize().y - 235 / lines - 65) / (lines)* (i + 1) - 35.f *this->timer.getScale().y);
		mapa->draw(this->timer);
		whole_text = loop+1;
	}
	if (whole_text < text.size())
	{
		this->timer.setString(text.substr(whole_text, text.size() - whole_text));
		this->timer.setPosition(mapa->getSize().x / 2 - 10.5 * this->timer.getScale().x *this->timer.getString().getSize(), (mapa->getSize().y - 235 / lines - 65));
		mapa->draw(this->timer);
	}
	



	mapa->display();

	sf::Event even;
	mapa->pollEvent(even);
	while (even.type != sf::Event::KeyPressed)
	{
		mapa->pollEvent(even);
	}
	mapa->clear();
}

template <class x>
void Cube<x>::moja_funkcja(World<Physical> *mapa)
{
	int q = 200;
	sf::CircleShape x(2, 3);
	//sf::CircleShape **x;
	//x = new sf::CircleShape*[q];
	
	for (int i = 0; i < q;i++)
	{
		//x[i] = new sf::CircleShape[q];
		for (int j = 0;j < q;j++)
		{
			/*
			x[i][j].setRadius(2);
			x[i][j].setPointCount(3);
			x[i][j].setOutlineColor(sf::Color::White);
			x[i][j].setFillColor(sf::Color::White);
			x[i][j].setPosition(sf::Vector2f(i,j));
			*/
		}
		
	}
	int t = 0;
	while (true)
	{
		int a = pow(t, 2);
		int b = pow(t, 3);
		
		for (int i = 0; i < q;i++)
		{
			for (int j = 0;j < q;j++)
			{
				x.setPosition(sf::Vector2f(i, j));
				//x.setOutlineColor(sf::Color(t+i+j,pow(t,2)+i*4+j,pow(t,3)+i+j*4, 255));
				x.setFillColor(sf::Color(b+j/2+pow(i,2)*2,t+j/2+pow(i,2)*2,a+j/2+pow(i,2)*2,255));
				mapa->draw(x);
			}

		}
		t++;
		mapa->display();
	}
	
	
	
	std::cin.ignore(1);
}
