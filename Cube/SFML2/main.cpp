
#include "Engine.h"
#include <vector>


/*  Copyright notice / uses
 


--------------- Based on Cube movie series -------------------
This is a student project, it does not make any commercial use,
it is not supposed to steal any rights of the movie idea.
This game imitates the movie general idea that someone
is trapped in a cube made of number of rooms
with said someone having to solve a puzzle.

Original movie name: Cube
Year: 1997
Directed by: Vincenzo Natali

   1. SFML API :
Original website: http://www.sfml-dev.org
License: https://opensource.org/licenses/Zlib

  2. Rabbit Sprite Sheets :
Credits: Art by Stephen "Redshrike" Challener and the OpenSurge Team ( http://opensnc.sourceforge.net). 
Commissioned by OpenGameArt.org (http://opengameart.org)
Original work possible to download: http://opengameart.org/content/surge-of-opensurge-for-ultimate-smash-friends
License: http://creativecommons.org/licenses/by/3.0/,
http://static.opengameart.org/OGA-BY-3.0.txt
Changes: An orange rabbit Sprite Sheet's background was changed to the color of grey one. 
Some animation frames were moved by specific offsets to remove frame overlapping.

  3. "Blazed" font :
Credits: author: Bright Ideas
Downloaded from: http://all-free-download.com/font/download/blazed_font_2082.html


4. Filth Texture set
By Georges "TRaK" Grondin
drognin@gmail.com
http://trak.mercenariesguild.net/

License: http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
Original work possible to download: http://opengameart.org/node/7230

5. Ladder
Credits: Marta Nowaczyk
Original work possible to download: http://opengameart.org/content/2d-platform-accessories
License: http://creativecommons.org/licenses/by/3.0/
Changes: Copied and pasted so ladder is twice as high.
-----------------------------------------------------------------------
Public Domain:
  6. Fire trap particles
  7. Roman column

 My sprites:
 8. Projectile
 9. Heal
*/


 //defined later here
 void Delete_Data(Sprite_Sheet_Data **graphics, sf::Texture *textures);
 Sprite_Sheet_Data **LOAD_graphics(sf::Texture *textures);
 sf::Texture *LOAD_texture();

int main()
{


	// make every other game different
	srand(time(NULL));
	
	
	
	// LOAD DATA
	sf::Texture *textures = LOAD_texture();
	Sprite_Sheet_Data **graphics = LOAD_graphics(textures);


	// CREATE GAME WORLD

	// create the world with its size, borders, max objects that is able to contain
	// it will keep a dynamic array of pointers to objects
	// it is also your window (derivates from RenderWindow)
	World<Physical> *mapa = new World<Physical>(sf::Vector2i(800,600), sf::Vector2i(40,30), 60);

	
	// CREATE PLAYER

	// create units from data loaded and pass world (to all physical objects too)
	Unit b(mapa->Get_objects(), *graphics[0], sf::Vector2f(mapa->Get_border_size().x/2+200, mapa->Get_border_size().y/2 + 200), mapa,  9.f, 500);
	//Unit a(38, lis2, sf::Vector2f(mapa->Get_border_size().x/2 + 60, mapa->Get_border_size().y/2 + 60), mapa,  9.f);



	// make units become players and define controls
	//Player x(a, mapa, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Numpad0, sf::Keyboard::Add, sf::Keyboard::Numpad9, sf::Keyboard::Numpad4);
	Player y(b, mapa);
	


	// CREATE GAME


	// create cube that controls all rooms in the game (after creating player)
	Cube<Room> *cube = new Cube<Room>(15, 3, 1, 0, graphics, mapa);

	//Cube<Room> *cube = new Cube<Room>(rand()%28, rand()%10+2, rand()%6+1, rand()%10, graphics, mapa, 144000);



	// CREATE ENGINE

	// create an engine to handle world, game and events
	Engine *engine = new Engine(cube, mapa);



	// START GAME

	// start game engine
	engine->run();



	//FINISH GAME

	//Delete all memory allocated
	Delete_Data(graphics, textures);

	
	return 0;
}


void Delete_Data(Sprite_Sheet_Data **graphics, sf::Texture *textures)
{
	//delete all effective_frames data
	delete[] graphics[0]->use.Get_type_of_animation_effective_frames();
	delete[] graphics[0]->kick.Get_type_of_animation_effective_frames();
	delete[] graphics[0]->attack.Get_type_of_animation_effective_frames();
	//delete all textures
	delete[] textures;
	//delete all graphics data
	for (int i = 0; i < graphic_set-1; i++)
	{
		
		
		delete graphics[i];
	}


	delete graphics[graphic_set];
	delete[]  graphics;
}

sf::Texture *LOAD_texture()
{
	// create and load image for sprite
	sf::Image imlis;
	imlis.loadFromFile(name_image_lis);

	sf::Image imlis2;
	imlis2.loadFromFile(name_image_lis2);

	sf::Image imfire;
	imfire.loadFromFile(name_image_fire);

	sf::Image improjectile;
	improjectile.loadFromFile(name_image_projectile);

	sf::Image imheal;
	imheal.loadFromFile(name_image_heal);

	sf::Image imredfloor;
	imredfloor.loadFromFile(name_image_red_floor);

	sf::Image imgreyfloor;
	imgreyfloor.loadFromFile(name_image_grey_floor);

	sf::Image imyellowfloor;
	imyellowfloor.loadFromFile(name_image_yellow_floor);

	sf::Image imexitborder;
	imexitborder.loadFromFile(name_image_exit_border);

	sf::Image imexitmiddle;
	imexitmiddle.loadFromFile(name_image_exit_middle);


	sf::Image imladder;
	imladder.loadFromFile(name_image_ladder);


	sf::Image imcolumn;
	imcolumn.loadFromFile(name_image_column);
	// mask color of loaded image background
	imlis.createMaskFromColor(sf::Color(0, 128, 128, 255));

	imlis2.createMaskFromColor(sf::Color(0, 128, 128, 255));

	imfire.createMaskFromColor(sf::Color(255, 255, 255, 255));

	improjectile.createMaskFromColor(sf::Color(0, 0, 0, 255));

	imheal.createMaskFromColor(sf::Color(255, 255, 255, 255));

	imladder.createMaskFromColor(sf::Color(255, 255, 255, 255));

	imcolumn.createMaskFromColor(sf::Color(255, 255, 255, 255));
	// create texture from image
	
	sf::Texture *textures = new sf::Texture[graphic_set];
	
	
	textures[0].loadFromImage(imlis);
	

	textures[1].loadFromImage(imlis2);


	textures[2].loadFromImage(imfire);
	

	textures[3].loadFromImage(improjectile);


	textures[4].loadFromImage(imheal);
	

	textures[5].loadFromImage(imredfloor);


	textures[6].loadFromImage(imgreyfloor);


	textures[7].loadFromImage(imyellowfloor);


	textures[8].loadFromImage(imexitborder);
	

	textures[9].loadFromImage(imexitmiddle);
	

	textures[10].loadFromImage(imladder);


	textures[11].loadFromImage(imcolumn);


	return textures;
}

Sprite_Sheet_Data **LOAD_graphics(sf::Texture *textures)
{
	// new variables for animated objects data
	Sprite_Sheet_Data *lis = new Sprite_Sheet_Data;
	Sprite_Sheet_Data *lis2 = new Sprite_Sheet_Data;

	Sprite_Sheet_Data *fire = new Sprite_Sheet_Data;
	Sprite_Sheet_Data *projectile = new Sprite_Sheet_Data;
	Sprite_Sheet_Data *heal = new Sprite_Sheet_Data;

	Sprite_Sheet_Data *background_r = new Sprite_Sheet_Data;
	Sprite_Sheet_Data *background_y = new Sprite_Sheet_Data;
	Sprite_Sheet_Data *background_g = new Sprite_Sheet_Data;

	Sprite_Sheet_Data *exitborder = new Sprite_Sheet_Data;
	Sprite_Sheet_Data *exitmiddle = new Sprite_Sheet_Data;
	Sprite_Sheet_Data *ladder = new Sprite_Sheet_Data;

	Sprite_Sheet_Data *column = new Sprite_Sheet_Data;


	//0-1 player skins
	//2-4 background
	// 5 - 7 exits (border,middle, ladder)
	// 8 column
	// 9 - 12 room features ( step, projectile, enemy, heal bonus)
	Sprite_Sheet_Data **graphics = new Sprite_Sheet_Data*[13];

	graphics[0] = lis;
	graphics[1] = lis2;
	graphics[2] = background_r;
	graphics[3] = background_y;
	graphics[4] = background_g;
	graphics[5] = exitborder;
	graphics[6] = exitmiddle;
	graphics[7] = ladder;
	graphics[8] = column;
	graphics[9] = fire;
	graphics[10] = projectile;
	graphics[11] = lis2;
	graphics[12] = heal;
	// initializing particular sheets data
	//lis
	//set it to number of frames before creating 'effective frames array' for 'type of animation'
	//and just copy 'block of effective frames initialization'

	int effective_frames_help = 0;
	// sprite sheet width
	lis->size = 1096;

	fire->size = 512;
	background_r->size = 256;
	ladder->size = 128;
	column->size = 256;
	projectile->size = 30;
	heal->size = 48;
	// size of object's body collision
	lis->width = 36; lis->height = 36;
	projectile->width = 16; projectile->height = 5;
	heal->width = 44; heal->height = 34;
	fire->width = 40; fire->height = 40;
	background_r->width = 256; background_r->height = 256;
	exitborder->width = 64; exitborder->height = 64;
	exitmiddle->width = 64; exitmiddle->height = 64;
	ladder->width = 50; ladder->height = 50;
	column->width = 36; column->height = 50;

	//creating animation data with number of frames, starting pixels, pixel jumps to another frame and size modifier for animation load purpose
	lis->still = Type_of_Animation(1, sf::Vector2i(2, 18), sf::Vector2i(68, 0), sf::Vector2i(18, 40));
	lis->go = Type_of_Animation(6, sf::Vector2i(8, 100), sf::Vector2i(68, 0), sf::Vector2i(18, 40));

	effective_frames_help = 6;
	// block of effective frames initialization
	int *lis_attack_effective_frames = new int[effective_frames_help];
	for (int i = 0; i < effective_frames_help; i++)
	{
		lis_attack_effective_frames[i] = 0;
	}
	// then you set your actually effective frames to desired values
	// 0 is no effect
	// 1 is attack that deals 1/5 of damage, interrupts enemy, does not damage blocking enemy
	// 2 deals full damage, knocks enemy back, deals 1 damage when blocked
	// 3 deals 110% damage no matter if enemy blocks, knocks back and up
	lis_attack_effective_frames[1] = 1;
	lis_attack_effective_frames[4] = 2;

	// more animations
	lis->attack = Type_of_Animation(6, sf::Vector2i(0, 448), sf::Vector2i(62, 0), sf::Vector2i(18, 40), lis_attack_effective_frames);
	lis->interrupted = Type_of_Animation(2, sf::Vector2i(280, 18), sf::Vector2i(0, 0), sf::Vector2i(18, 40));
	lis->hit = Type_of_Animation(2, sf::Vector2i(214, 17), sf::Vector2i(0, 0), sf::Vector2i(18, 40));
	lis->block = Type_of_Animation(1, sf::Vector2i(55, 274), sf::Vector2i(0, 0), sf::Vector2i(18, 40));



	projectile->still = Type_of_Animation(1, sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(14, 25));
	heal->still = Type_of_Animation(1, sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(4, 14));
	projectile->go = Type_of_Animation(1, sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(14, 25));

	fire->still = Type_of_Animation(64, sf::Vector2i(0, 0), sf::Vector2i(128, 128), sf::Vector2i(88, 88), NULL, 8, sf::Vector2i(0, 12));

	ladder->still = Type_of_Animation(1, sf::Vector2i(0, 0), sf::Vector2i(128, 128), sf::Vector2i(78, 78), NULL, 0, sf::Vector2i(-ladder->width / 2, -ladder->height / 2));

	column->still = Type_of_Animation(1, sf::Vector2i(0, 0), sf::Vector2i(256, 640), sf::Vector2i(220, 590), NULL, 0, sf::Vector2i(-column->width / 2, -column->height / 2 + 100));

	effective_frames_help = 4;
	int *lis_kick_effective_frames = new int[effective_frames_help];
	for (int i = 0; i < effective_frames_help; i++)
	{
		lis_kick_effective_frames[i] = 0;
	}
	lis_kick_effective_frames[3] = 3;
	lis->kick = Type_of_Animation(4, sf::Vector2i(0, 748), sf::Vector2i(72, 0), sf::Vector2i(34, 40), lis_kick_effective_frames);

	effective_frames_help = 30;
	int *lis_use_effective_frames = new int[effective_frames_help];
	for (int i = 0; i < effective_frames_help; i++)
	{
		lis_use_effective_frames[i] = 0;
	}
	lis_use_effective_frames[29] = 1;
	lis->use = Type_of_Animation(30, sf::Vector2i(54, 360), sf::Vector2i(0, 0), sf::Vector2i(44, 40), lis_use_effective_frames);
	// copying data to another skin of the character
	*lis2 = *lis;
	*background_g = *background_r;
	*background_y = *background_r;
	
	// create sprite from texture with starting pixels of picture that should be shown at first and its width and height of view (not necessary for animated)
	
	
	sf::Sprite xslis = sf::Sprite(textures[0], sf::IntRect(0, 0, lis->width, lis->height));

	sf::Sprite xslis2 = sf::Sprite(textures[1], sf::IntRect(0, 0, lis->width, lis->height));

	sf::Sprite xsfire = sf::Sprite(textures[2], sf::IntRect(0, 0, fire->width, fire->height));

	sf::Sprite xsprojectile = sf::Sprite(textures[3], sf::IntRect(0, 0, projectile->width, projectile->height));

	sf::Sprite xsheal =sf::Sprite(textures[4], sf::IntRect(0, 0, heal->width, heal->height));

	sf::Sprite xsredfloor =sf::Sprite(textures[5], sf::IntRect(0, 0, 256, 256));

	sf::Sprite xsgreyfloor = sf::Sprite(textures[6], sf::IntRect(0, 0, 256, 256));

	sf::Sprite xsyellowfloor = sf::Sprite(textures[7], sf::IntRect(0, 0, 256, 256));

	sf::Sprite xsexitborder = sf::Sprite(textures[8], sf::IntRect(0, 0, 64, 64));

	sf::Sprite xsexitmiddle = sf::Sprite(textures[9], sf::IntRect(0, 0, 64, 64));

	sf::Sprite xsladder = sf::Sprite(textures[10], sf::IntRect(0, 0, 128, 128));

	sf::Sprite xscolumn = sf::Sprite(textures[11], sf::IntRect(0, 0, 256, 640));
	// set scales
	xsfire.setScale(0.5, 0.5);

	xsladder.setScale(0.4, 0.5);

	xscolumn.setScale(0.25, 0.25);
	// send a refence of sprite to data
	lis->data = xslis;

	lis2->data = xslis2;

	fire->data = xsfire;
	projectile->data = xsprojectile;
	heal->data = xsheal;
	background_r->data = xsredfloor;
	background_y->data = xsyellowfloor;
	background_g->data = xsgreyfloor;
	exitborder->data = xsexitborder;
	exitmiddle->data = xsexitmiddle;

	ladder->data = xsladder;

	column->data = xscolumn;


	// DATA LOADING FINISHED
	return graphics;
}